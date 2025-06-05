#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite) : Piece(isWhite, isWhite ? 'P' : 'p') {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const override;
    bool isPromotion(int row) const;
    Piece* clone() const override { return new Pawn(*this); }  // Implement clone method
};