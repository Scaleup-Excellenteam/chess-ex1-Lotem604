#include "Game.h"
#include "King.h"
#include "Rook.h"
#include "Pawn.h"
#include "Chess.h"
#include <iostream>

int Game::processInput(const string& input) {
    int srcRow = input[0] - 'a';
    int srcCol = input[1] - '1';
    int destRow = input[2] - 'a';
    int destCol = input[3] - '1';

    Piece* srcPiece = board.getPiece(srcRow, srcCol);
    Piece* destPiece = board.getPiece(destRow, destCol);

    if (!srcPiece) {
        std::cout << "No piece at source position\n";
        return CR_NO_PIECE;
    }

    if (srcPiece->isWhitePiece() != turn) {
        std::cout << "Piece belongs to the opponent\n";
        return CR_WRONG_TURN;
    }

    if (destPiece && destPiece->isWhitePiece() == turn && !(srcPiece->getSymbol() == 'K' && destPiece->getSymbol() == 'R')) {
        std::cout << "Destination occupied by same color piece\n";
        return CR_SAME_COLOR;
    }

    if (!srcPiece->isValidMove(srcRow, srcCol, destRow, destCol, board.getBoard())) {
        std::cout << "Invalid move for the piece\n";
        return CR_INVALID_MOVE;
    }

    Piece* tempDest = destPiece;
    board.movePiece(srcRow, srcCol, destRow, destCol);

    if (board.isCheck(turn)) {
        board.movePiece(destRow, destCol, srcRow, srcCol);
        board.setPiece(destRow, destCol, tempDest);
        std::cout << "Move would cause check\n";
        return CR_SELF_CHECK;
    }
    bool oppInCheck = board.isCheck(!turn);
    switchTurn();
    if (oppInCheck) {
    return CR_OPPONENT_CHECK;
    } else {
    return CR_MOVE_OK;
    }
}