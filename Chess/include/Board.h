#include "Piece.h"
#include <string>
#include <iostream>

using std::string;

class Board {
    Piece* board[8][8];
public:
    explicit Board(const string& start);
    bool movePiece(int srcRow, int srcCol, int destRow, int destCol);
    bool isCheck(bool isWhite) const;
    bool isCheckmate(bool isWhite);
    Piece* getPiece(int row, int col) const { return board[row][col]; }
    void setPiece(int row, int col, Piece* piece) { board[row][col] = piece; }
    Piece* const (*getBoard() const)[8] { return board; }
    bool promotePawn(int row, int col, char newPieceType);
    ~Board();
};