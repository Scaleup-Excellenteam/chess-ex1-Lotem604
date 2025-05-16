#pragma once
#include <string>
#include <iostream>

class Move {
public:
    Move(int srcRow, int srcCol, int destRow, int destCol, char pieceSymbol, int score = 0)
            : srcRow(srcRow), srcCol(srcCol), destRow(destRow), destCol(destCol), pieceSymbol(pieceSymbol), score(score) {}

    std::string toString() const;
    int getScore() const;
    void setScore(int newScore);

    int getSrcRow() const { return srcRow; }
    int getSrcCol() const { return srcCol; }
    int getDestRow() const { return destRow; }
    int getDestCol() const { return destCol; }
    char getPieceSymbol() const { return pieceSymbol; }

    friend std::ostream& operator<<(std::ostream& os, const Move& move);

private:
    int srcRow;
    int srcCol;
    int destRow;
    int destCol;
    char pieceSymbol;
    int score;
};