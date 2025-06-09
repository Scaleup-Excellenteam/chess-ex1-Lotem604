#include "Chess.h"
#include "Game.h"
#include <iostream>
#include <sstream>

int main() {
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess a(board);
    int codeResponse = 0;
    string res = a.getInput();
    Game game(board);
    while (res != "exit") {
        codeResponse = game.processInput(res);
        a.setCodeResponse(codeResponse);
        PriorityQueue<Move, MoveComparator> pq(5);  
        game.getBoard().findBestMoves(game.isWhiteTurn(), pq);
        std::stringstream ss;
        ss << "Top 3 move recommendations:\n";
        for (int i = 0; i < 3 && !pq.isEmpty(); ++i) {
            ss << pq.poll().toString() << std::endl;
        }
        a.bestMove(ss.str());
        res = a.getInput();
    }
    std::cout << "Press any key to exit...\n";
    std::cin.ignore();
    std::cin.get();
    std::cout << "Exiting " << std::endl;
    return 0;
}