#include "Chess.h"
#include "Board.h"
#include <iostream>
using namespace std;

int main() {
    string boardStr = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess chess(boardStr);
    Board board(boardStr);

    bool isWhiteTurn = true; 
    string res = chess.getInput();

    while (res != "exit") {
        int codeResponse = 0;

        int srcRow = res[0] - 'a';
        int srcCol = res[1] - '1';
        int destRow = res[2] - 'a';
        int destCol = res[3] - '1';

        Piece* piece = board.getPiece(srcRow, srcCol);
        Piece* target = board.getPiece(destRow, destCol);

        if (!piece)
            codeResponse = 11;
        else if (piece->isWhitePiece() != isWhiteTurn)
            codeResponse = 12;
        else if (target && target->isWhitePiece() == piece->isWhitePiece())
            codeResponse = 13;
        else if (!piece->isValidMove(srcRow, srcCol, destRow, destCol, board.getBoard()))
            codeResponse = 21;
        else {
            Piece* temp = board.getPiece(destRow, destCol);
            board.setPiece(destRow, destCol, piece);
            board.setPiece(srcRow, srcCol, nullptr);
            bool isCheck = board.isCheck(isWhiteTurn);
            board.setPiece(srcRow, srcCol, piece);
            board.setPiece(destRow, destCol, temp);

            if (isCheck)
                codeResponse = 31;
            else {
                board.movePiece(srcRow, srcCol, destRow, destCol);
                bool causesCheck = board.isCheck(!isWhiteTurn);
                codeResponse = causesCheck ? 41 : 42;
                isWhiteTurn = !isWhiteTurn;
            }
        }

        chess.setCodeResponse(codeResponse);
        res = chess.getInput();
    }

    cout << "\nExiting" << endl;
    return 0;
}
