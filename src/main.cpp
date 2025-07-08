#include "Chess.h"
#include "Game.h"
#include "AutoGameRunner.h"
#include "ThreadPool.h"
#include "MoveComparator.h"
#include "PriorityQueue.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int depth, threshold, numThreads=8, mode;

    std::cout << "Enter minimax depth: ";
    std::cin >> depth;

    std::cout << "Enter score threshold for early stop: ";
    std::cin >> threshold;
    
    std::cout << "Select mode:\n"
              << "  1 = Player vs AI\n"
              << "  2 = Auto AI vs AI\n"
              << "  3 = Player vs Player\n"
              << "Your choice: ";
    std::cin >> mode;

    std::string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";

    if (mode == 2) {
        AutoGameRunner::runAutoGame(depth, threshold, numThreads);
        return 0;
    }

    Chess a(board);
    Game game(board);
    ThreadPool pool(numThreads);
    int codeResponse = 0;
    std::string res;

    bool playerIsWhite = true;

    if (mode == 1) {
        char colorChoice;
        do {
            std::cout << "Do you want to play as white (w) or black (b)? ";
            std::cin >> colorChoice;
        } while (colorChoice != 'w' && colorChoice != 'b');
        playerIsWhite = (colorChoice == 'w');
    }

    while (true) {
        if (mode == 1 && game.isWhiteTurn() != playerIsWhite) {
            try {
                PriorityQueue<Move, MoveComparator> pq(5);
                game.getBoard().findBestMoves(game.isWhiteTurn(), pq);
                std::vector<Move> topMoves;
                for (int i = 0; i < 3 && !pq.isEmpty(); ++i) {
                    topMoves.push_back(pq.poll());
                }

                if (topMoves.empty()) {
                    std::cout << "AI has no valid moves.\n";
                    break;
                }

                Move best = topMoves[rand() % topMoves.size()];
                std::stringstream fakeInput;
                fakeInput << char('a' + best.getSrcRow())
                          << (best.getSrcCol() + 1)
                          << char('a' + best.getDestRow())
                          << (best.getDestCol() + 1);
                codeResponse = game.processInput(fakeInput.str());
                a.setCodeResponse(codeResponse);

                std::stringstream ss;
                ss << "AI played: " << best.toString();
                a.bestMove(ss.str());
                a.displayBoard();
            } catch (const std::exception& e) {
                a.bestMove("AI error: " + std::string(e.what()));
                a.displayBoard();
                break;
            }
        } else {
            res = a.getInput();
            if (res == "exit") break;
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
        }
    }

    std::cout << "Exiting..." << std::endl;
    return 0;
}
