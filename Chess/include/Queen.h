#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(bool isWhite) : Piece(isWhite, isWhite ? 'Q' : 'q') {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const override;
    Piece* clone() const override { return new Queen(*this); }  // Implement clone method
};