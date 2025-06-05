#include "AutoGameRunner.h"
#include "PriorityQueue.h"
#include "MoveComparator.h"
#include <thread>

void AutoGameRunner::runAutoGame(int depth, int threshold, int numThreads, int maxPlies) {
    std::string initialBoard = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Board board(initialBoard);

    bool isWhiteTurn = true;
    int moveCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    if (numThreads == 0) {
        while (moveCount < maxPlies) {
            try {
                PriorityQueue<Move, MoveComparator> pq(64);
                board.findBestMoves(isWhiteTurn, pq);
                if (pq.isEmpty()) break;
                Move bestMove = pq.poll();
                board.movePiece(bestMove.getSrcRow(), bestMove.getSrcCol(), bestMove.getDestRow(), bestMove.getDestCol());

                std::cout << (isWhiteTurn ? "White" : "Black") << " plays: " << bestMove.toString() << "\n";

                if (board.isCheckmate(!isWhiteTurn)) {
                    std::cout << (isWhiteTurn ? "White" : "Black") << " wins by checkmate!\n";
                    break;
                }
                isWhiteTurn = !isWhiteTurn;
                ++moveCount;
            } catch (const std::exception& e) {
                std::cerr << "No valid moves or error: " << e.what() << "\n";
                break;
            }
        }
    } else {
        ThreadPool pool(numThreads);
        while (moveCount < maxPlies) {
            try {
                Move bestMove = board.getBestMoveWithPool(isWhiteTurn, pool, depth, threshold);
                board.movePiece(bestMove.getSrcRow(), bestMove.getSrcCol(), bestMove.getDestRow(), bestMove.getDestCol());

                std::cout << (isWhiteTurn ? "White" : "Black") << " plays: " << bestMove.toString() << "\n";

                if (board.isCheckmate(!isWhiteTurn)) {
                    std::cout << (isWhiteTurn ? "White" : "Black") << " wins by checkmate!\n";
                    break;
                }

                isWhiteTurn = !isWhiteTurn;
                ++moveCount;
            } catch (const std::exception& e) {
                std::cerr << "No valid moves or error: " << e.what() << "\n";
                break;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "\nAuto game finished in " << duration << " ms using " << numThreads << " threads." << std::endl;
}
