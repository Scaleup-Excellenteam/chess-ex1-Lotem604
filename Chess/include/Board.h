#pragma once
#include "Piece.h"
#include "PriorityQueue.h"
#include "Move.h"
#include "MoveComparator.h"
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

    // Best move related methods
    void findBestMoves(bool isWhiteTurn, PriorityQueue<Move, MoveComparator>& pq) const;
    Move getBestMove(bool isWhiteTurn) const;
    
private:
    int evaluateMove(const Move& move, bool isWhiteTurn) const;
    int minimax(int depth, bool isWhiteTurn, int alpha, int beta) const;
    static const int MAX_DEPTH = 2;  // Depth limit
    
    bool isCheck(Piece* const board[8][8], bool isWhiteTurn) const;
    bool isCheckmate(Piece* const board[8][8], bool isWhiteTurn) const;
};