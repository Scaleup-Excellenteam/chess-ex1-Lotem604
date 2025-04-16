#include "Pawn.h"
#include <cstdlib>

bool Pawn::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const (*board)[8]) const {
    if (isWhitePiece()) {
        if (srcCol == destCol) {
            if (destRow == srcRow + 1 && board[destRow][destCol] == nullptr) {
                return true;
            }
            if (srcRow == 1 && destRow == 3 && board[2][destCol] == nullptr && board[3][destCol] == nullptr) {
                return true;
            }
        }
        if (abs(srcCol - destCol) == 1 && destRow == srcRow + 1) {
            Piece* targetPiece = board[destRow][destCol];
            if (targetPiece != nullptr && targetPiece->isWhitePiece() != this->isWhitePiece()) {
                return true;
            }
        }
    } else { 
        if (srcCol == destCol) {
            if (destRow == srcRow - 1 && board[destRow][destCol] == nullptr) {
                return true;
            }
            if (srcRow == 6 && destRow == 4 && board[5][destCol] == nullptr && board[4][destCol] == nullptr) {
                return true;
            }
        }
        if (abs(srcCol - destCol) == 1 && destRow == srcRow - 1) {
            Piece* targetPiece = board[destRow][destCol];
            if (targetPiece != nullptr && targetPiece->isWhitePiece() != this->isWhitePiece()) {
                return true;
            }
        }
    }
    return false;
}

bool Pawn::isPromotion(int row) const {
    return (isWhitePiece() && row == 7) || (!isWhitePiece() && row == 0);
}