#pragma once
#include "Piece.h"

class King : public Piece {
public:
    King(bool isWhite) : Piece(isWhite, isWhite ? 'K' : 'k'), moved(false) {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const override;
    bool isCastlingMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const;
    bool canCastle(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const;
    void setMoved(bool hasMoved) { moved = hasMoved; }
    bool hasMoved() const { return moved; }
    Piece* clone() const override { return new King(*this); }  // Implement clone method
private:
    bool moved;
    bool KingUnderAttack(int row, int col, bool color, Piece* const board[8][8]) const;
};