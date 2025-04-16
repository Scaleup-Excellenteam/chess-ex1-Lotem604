#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(bool isWhite) : Piece(isWhite, isWhite ? 'R' : 'r'), moved(false) {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const override;
    void setMoved(bool hasMoved);
    bool hasMoved() const;
    Piece* clone() const override { return new Rook(*this); }  // Implement clone method
private:
    bool moved;
};