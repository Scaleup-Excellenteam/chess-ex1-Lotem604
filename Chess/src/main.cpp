#include "Chess.h"
#include "Game.h"
#include "AutoGameRunner.h"
#include "ThreadPool.h"
#include <iostream>
#include <sstream>

int main() {
    int depth, threshold, numThreads, mode;

    std::cout << "Enter minimax depth: ";
    std::cin >> depth;

    std::cout << "Enter score threshold for early stop: ";
    std::cin >> threshold;

    do {
        std::cout << "Enter number of threads to use (0, 2, 4, 8): ";
        std::cin >> numThreads;
    } while (numThreads != 0 && numThreads != 2 && numThreads != 4 && numThreads != 8);

    std::cout << "Select mode:\n"
              << "  1 = Player vs AI\n"
              << "  2 = Auto AI vs AI\n"
              << "Your choice: ";
    std::cin >> mode;

    if (mode == 2) {
        AutoGameRunner::runAutoGame(depth, threshold, numThreads);
        return 0;
    }

    std::string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess a(board);
    int codeResponse = 0;
    std::string res = a.getInput();
    Game game(board);
    ThreadPool pool(numThreads);

    while (res != "exit") {
        codeResponse = game.processInput(res);
        a.setCodeResponse(codeResponse);

        try {
            Move best = game.getBoard().getBestMoveWithPool(game.isWhiteTurn(), pool, depth, threshold);
            std::stringstream ss;
            ss << "Recommended move: " << best.toString();
            a.bestMove(ss.str());
        } catch (const std::exception& e) {
            a.bestMove("No recommendation: " + std::string(e.what()));
        }

        res = a.getInput();
    }

    std::cout << "Press any key to exit...\n";
    std::cin.ignore();
    std::cin.get();
    std::cout << "Exiting " << std::endl;
    return 0;
}
