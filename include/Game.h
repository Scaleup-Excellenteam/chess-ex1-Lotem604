#pragma once
#include "Board.h"
#include <string>
using std::string;

class Game {
    Board board;
    bool turn = true; // true for white's turn, false for black's turn
public:
    Game(const string& start) : board(start), turn(true) {}
    int processInput(const string& input);
    void switchTurn() { turn = !turn; }
    bool isWhiteTurn() const { return turn; }
    Board& getBoard() { return board; }
};