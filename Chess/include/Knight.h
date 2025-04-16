#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(bool isWhite) : Piece(isWhite, isWhite ? 'N' : 'n') {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const override;
    Piece* clone() const override { return new Knight(*this); }  // Implement clone method
};