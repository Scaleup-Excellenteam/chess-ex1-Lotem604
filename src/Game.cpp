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

    if ((srcPiece->getSymbol() == 'K' || srcPiece->getSymbol() == 'k') && srcCol == 4 && (destCol == 0 || destCol == 7)) {
        int rookSrcCol = destCol;
        int rookDestCol = (destCol == 0) ? 3 : 5;
        int kingDestCol = (destCol == 0) ? 2 : 6;
        board.movePiece(srcRow, srcCol, srcRow, kingDestCol); // Move the king
        board.movePiece(srcRow, rookSrcCol, srcRow, rookDestCol); // Move the rook

        dynamic_cast<King*>(srcPiece)->setMoved(true);
        dynamic_cast<Rook*>(board.getPiece(srcRow,rookDestCol))->setMoved(true);
        switchTurn();
        return CR_CASTLING;
    }

    Piece* tempDest = destPiece;
    board.movePiece(srcRow, srcCol, destRow, destCol);

    if (board.isCheck(turn)) {
        board.movePiece(destRow, destCol, srcRow, srcCol);
        board.setPiece(destRow, destCol, tempDest);
        std::cout << "Move would cause check\n";
        return CR_SELF_CHECK;
    }

    if (Pawn* pawn = dynamic_cast<Pawn*>(srcPiece)) {
        if (pawn->isPromotion(destRow)) {
            std::cout << "Pawn promotion! Enter new piece type (Q/R/B/N): ";
            char newPieceType;
            std::cin >> newPieceType;
            if (!board.promotePawn(destRow, destCol, newPieceType)) {
                return CR_INVALID_PROMOTION;
            }
            switchTurn();
            return CR_PROMOTION;
        }
    }

    if (board.isCheck(!turn)) {
        if (board.isCheckmate(!turn)) {
            std::cout << "Checkmate detected for " << (turn ? "Black" : "White") << std::endl;
            return CR_CHECKMATE;
        }
        return CR_OPPONENT_CHECK;
    }
    if (!board.hasAnyLegalMove(!turn)) {
        if (!board.isCheck(!turn)) {
            std::cout << "Stalemate!\n";
            return CR_STALEMATE;
    }
}

    switchTurn();
    return CR_MOVE_OK;
}