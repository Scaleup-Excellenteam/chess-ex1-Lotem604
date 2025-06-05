#include <valarray>
#include "Queen.h"


bool Queen::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece *const (*board)[8]) const {
    int rowDiff = abs(destRow - srcRow);
    int colDiff = abs(destCol - srcCol);
    if (rowDiff == colDiff || srcRow == destRow || srcCol == destCol) {
        int rowStep = (destRow > srcRow) ? 1 : (destRow < srcRow) ? -1 : 0;
        int colStep = (destCol > srcCol) ? 1 : (destCol < srcCol) ? -1 : 0;

        int currentRow = srcRow + rowStep;
        int currentCol = srcCol + colStep;

        while (currentRow != destRow || currentCol != destCol) {
            if (board[currentRow][currentCol] != nullptr) {
                return false;
            }
            currentRow += rowStep;
            currentCol += colStep;
        }
        Piece* targetPiece = board[destRow][destCol];
        if (targetPiece == nullptr || targetPiece->isWhitePiece() != this->isWhitePiece()) {
            return true;
        }
    }

    return false;
}