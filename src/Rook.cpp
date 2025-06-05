#include "Rook.h"

bool Rook::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const {
    // Rook moves horizontally or vertically
    if (srcRow != destRow && srcCol != destCol) return false; // Rook can't move diagonally

    // Check if path is clear
    if (srcRow == destRow) {
        int step = (srcCol < destCol) ? 1 : -1;
        for (int col = srcCol + step; col != destCol; col += step) {
            if (board[srcRow][col] != nullptr) return false;
        }
    } else {
        int step = (srcRow < destRow) ? 1 : -1;
        for (int row = srcRow + step; row != destRow; row += step) {
            if (board[row][srcCol] != nullptr) return false;
        }
    }

    return true;
}

bool Rook::hasMoved() const {
    return moved;
}

void Rook::setMoved(bool hasMoved) {
    moved = hasMoved;
}