#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include <stdexcept>
#include "Chess.h"
#include <iostream>
using namespace std;

Board::Board(const string& start) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
            char c = start[i * 8 + j];
            bool isWhite = isupper(c);
            c = tolower(c);

            switch (c) {
                case 'r': board[i][j] = new Rook(isWhite); break;
                case 'k': board[i][j] = new King(isWhite); break;
                case 'p': board[i][j] = new Pawn(isWhite); break;
                case 'q': board[i][j] = new Queen(isWhite); break;
                case 'b': board[i][j] = new Bishop(isWhite); break;
                case 'n': board[i][j] = new Knight(isWhite); break;
                case '#': board[i][j] = nullptr; break;
                default:
                    throw std::invalid_argument("Invalid piece character");
            }
        }
    }
}

bool Board::movePiece(int srcRow, int srcCol, int destRow, int destCol) {
    Piece* piece = board[srcRow][srcCol];
    board[destRow][destCol] = piece;
    board[srcRow][srcCol] = nullptr;
    return true;
}

bool Board::isCheck(bool isWhite) const {
    char kingSymbol = isWhite ? 'K' : 'k';
    int kingRow = -1, kingCol = -1;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];
            if (piece && piece->getSymbol() == kingSymbol) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    if (kingRow == -1 || kingCol == -1) return false;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];
            if (piece && piece->isWhitePiece() != isWhite &&
                piece->isValidMove(row, col, kingRow, kingCol, board)) {
                return true;
            }
        }
    }

    return false;
}

bool Board::promotePawn(int row, int col, char newPieceType) {
    if (tolower(newPieceType) != 'q' && tolower(newPieceType) != 'r' &&
        tolower(newPieceType) != 'b' && tolower(newPieceType) != 'n') {
        return false;
    }

    bool isWhite = board[row][col]->isWhitePiece();
    delete board[row][col];

    switch (tolower(newPieceType)) {
        case 'q': board[row][col] = new Queen(isWhite); break;
        case 'r': board[row][col] = new Rook(isWhite); break;
        case 'b': board[row][col] = new Bishop(isWhite); break;
        case 'n': board[row][col] = new Knight(isWhite); break;
    }

    return true;
}

Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
}