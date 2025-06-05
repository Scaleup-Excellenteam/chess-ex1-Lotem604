#include "Bishop.h"
#include <cmath>
bool Bishop::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece *const (*board)[8]) const {
    int rowDiff = abs(destRow - srcRow);
    int colDiff = abs(destCol - srcCol);
    // Bishops move diagonally
    if (rowDiff == colDiff) {
        int rowStep = (destRow > srcRow) ? 1 : -1;
        int colStep = (destCol > srcCol) ? 1 : -1;
        int currentRow = srcRow + rowStep;
        int currentCol = srcCol + colStep;

        while (currentRow != destRow && currentCol != destCol) {
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