#include <cstdlib>
#include <iostream>
#include "King.h"
#include "Rook.h"

bool King::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const {
    // Regular king move
    if (abs(srcRow - destRow) <= 1 && abs(srcCol - destCol) <= 1) {
        if (board[destRow][destCol] == nullptr || board[destRow][destCol]->isWhitePiece() != this->isWhitePiece()) {
            return true;
        }
    }
    // Castling move
    if (isCastlingMove(srcRow, srcCol, destRow, destCol, board)) {
        return canCastle(srcRow, srcCol, destRow, destCol, board);
    }
    return false;
}

// Check if a move is a valid castling move
bool King::isCastlingMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const {
    if (this->moved) return false;

    if (destRow == srcRow && (destCol == 0 || destCol == 7)) {
        Piece* rook = board[destRow][destCol];
        if (rook && (rook->getSymbol() == 'R' || rook->getSymbol() == 'r') && rook->isWhitePiece() == this->isWhitePiece()) {
            Rook* rookPiece = dynamic_cast<Rook*>(rook);
            if (rookPiece && !rookPiece->hasMoved()) {
                int step = (destCol > srcCol) ? 1 : -1;
                for (int col = srcCol + step; col != destCol; col += step) {
                    if (board[srcRow][col] != nullptr) return false;
                }
                return true;
            }
        }
    }
    return false;
}

// Check if the king can castle
bool King::canCastle(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const {
    int step = (destCol > srcCol) ? 1 : -1;
    for (int col = srcCol + step; col != destCol; col += step) {
        if (board[srcRow][col] != nullptr) return false;
        // Ensure the king is not in check, passing through check, or ending up in check
    }
    int kingDestY = (destCol == 0) ? 2 : 6;
    if (KingUnderAttack(srcRow, srcCol + step, this->isWhitePiece(), board) ||
        KingUnderAttack(srcRow, kingDestY, this->isWhitePiece(), board)){
        return false;
    }
    return true;
}


bool King::KingUnderAttack(int row, int col, bool color, Piece* const board[8][8]) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0;j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece && piece->isWhitePiece() != color && piece->isValidMove(i, j, row, col, board)) {
                return true;
            }
        }
    }
    return false;
}