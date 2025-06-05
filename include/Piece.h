#pragma once
class Piece {
public:
    bool isWhite;
    char symbol;
public:
    Piece(bool isWhite, char symbol) : isWhite(isWhite), symbol(symbol) {}
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* const board[8][8]) const = 0;
    bool isWhitePiece() const { return isWhite; }
    char getSymbol() const { return symbol; }
    virtual Piece* clone() const = 0;  // Add clone method
    virtual ~Piece() {}
};