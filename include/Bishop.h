#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(bool isWhite) : Piece(isWhite, isWhite ? 'B' : 'b') {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const override;
    Piece* clone() const override { return new Bishop(*this); }  // Implement clone method
};