#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Exceptions.h"

// Define piece values
int getPieceValue(char piece) {
    switch (tolower(piece)) {
        case 'p': return 1;   // Pawn
        case 'n': return 3;   // Knight
        case 'b': return 3;   // Bishop
        case 'r': return 5;   // Rook
        case 'q': return 9;   // Queen
        case 'k': return 100; // King (usually very high to avoid losing king)
        default: return 0;
    }
}

Board::Board(const string& start) {
    // Initialize board based on the start string
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr; // Ensure all pointers are initialized
            char c = start[i * 8 + j];
            bool isWhite = isupper(c);
            c = tolower(c);

            switch (c) {
                case 'r':
                    board[i][j] = new Rook(isWhite);
                    break;
                case 'k':
                    board[i][j] = new King(isWhite);
                    break;
                case 'p':
                    board[i][j] = new Pawn(isWhite);
                    break;
                case 'q':
                    board[i][j] = new Queen(isWhite);
                    break;
                case 'b':
                    board[i][j] = new Bishop(isWhite);
                    break;
                case 'n':
                    board[i][j] = new Knight(isWhite);
                    break;
                case '#':
                    board[i][j] = nullptr;
                    break;
                default:
                    throw std::invalid_argument("Invalid piece character");
            }
        }
    }
}

bool Board::movePiece(int srcRow, int srcCol, int destRow, int destCol) {
    Piece* piece = board[srcRow][srcCol];
    if (!piece) {
        throw InvalidMoveException("No piece at source position");
    }
    if (!piece->isValidMove(srcRow, srcCol, destRow, destCol, board)) {
        throw InvalidMoveException("Invalid move for the piece");
    }
    // Move the piece and update the board
    board[destRow][destCol] = piece;
    board[srcRow][srcCol] = nullptr;
    return true;
}

bool Board::isCheck(bool isWhite) const {
    char kingSymbol = (isWhite) ? 'K' : 'k';
    int kingRow = -1, kingCol = -1;

    // Find the king's position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];
            if (piece && piece->getSymbol() == kingSymbol) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    if (kingRow == -1 || kingCol == -1) return false;

    // Check if any opponent piece can move to the king's position
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];
            if (piece && piece->isWhitePiece() != isWhite && piece->isValidMove(row, col, kingRow, kingCol, board)) {
                return true;
            }
        }
    }
    return false;
}

bool Board::isCheckmate(bool isWhite) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board[row][col];
            if (piece && piece->isWhitePiece() == isWhite) {
                for (int destRow = 0; destRow < 8; ++destRow) {
                    for (int destCol = 0; destCol < 8; ++destCol) {
                        if (piece->isValidMove(row, col, destRow, destCol, board)) {
                            Piece* temp = board[destRow][destCol];
                            board[destRow][destCol] = piece;
                            board[row][col] = nullptr;
                            bool check = isCheck(isWhite);
                            board[row][col] = piece;
                            board[destRow][destCol] = temp;
                            if (!check) {
                                return false; // Not checkmate if there is at least one valid move
                            }
                        }
                    }
                }
            }
        }
    }
    return true; // Checkmate if no valid moves found
}

bool Board::promotePawn(int row, int col, char newPieceType) {
    if (tolower(newPieceType) != 'q' && tolower(newPieceType) != 'r' && tolower(newPieceType) != 'b' && tolower(newPieceType) != 'n') {
        throw PromotionException("Invalid piece type for promotion");
    }
    bool isWhite = board[row][col]->isWhitePiece();
    delete board[row][col];

    switch (tolower(newPieceType)) {
        case 'q':
            board[row][col] = new Queen(isWhite);
            break;
        case 'r':
            board[row][col] = new Rook(isWhite);
            break;
        case 'b':
            board[row][col] = new Bishop(isWhite);
            break;
        case 'n':
            board[row][col] = new Knight(isWhite);
            break;
    }
    return true;
}

Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
}

// Best move related methods

void Board::findBestMoves(bool isWhiteTurn, PriorityQueue<Move, MoveComparator>& pq) const {
    for (int srcRow = 0; srcRow < 8; ++srcRow) {
        for (int srcCol = 0; ++srcCol < 8; ++srcCol) {
            Piece* piece = board[srcRow][srcCol];
            if (piece && piece->isWhitePiece() == isWhiteTurn) {
                for (int destRow = 0; destRow < 8; ++destRow) {
                    for (int destCol = 0; destCol < 8; ++destCol) {
                        if (piece->isValidMove(srcRow, srcCol, destRow, destCol, board)) {
                            // Check if the move is valid by making a copy of the board and applying the move
                            Piece* tempBoard[8][8] = {nullptr};
                            for (int i = 0; i < 8; ++i) {
                                for (int j = 0; j < 8; ++j) {
                                    if (board[i][j]) {
                                        tempBoard[i][j] = board[i][j]->clone();
                                    }
                                }
                            }
                            tempBoard[destRow][destCol] = tempBoard[srcRow][srcCol];
                            tempBoard[srcRow][srcCol] = nullptr;

                            if (!isCheck(tempBoard, isWhiteTurn)) {
                                Move move(srcRow, srcCol, destRow, destCol, piece->getSymbol());
                                int score = evaluateMove(move, isWhiteTurn);
                                move.setScore(score);
                                pq.push(move);
                            }

                            // Clean up the temporary board
                            for (int i = 0; i < 8; ++i) {
                                for (int j = 0; j < 8; ++j) {
                                    delete tempBoard[i][j];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int Board::evaluateMove(const Move& move, bool isWhiteTurn) const {
    // Create a temporary board
    Piece* tempBoard[8][8] = {nullptr};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j]) {
                tempBoard[i][j] = board[i][j]->clone();
            }
        }
    }

    // Perform the move on the temporary board
    tempBoard[move.getDestRow()][move.getDestCol()] = tempBoard[move.getSrcRow()][move.getSrcCol()];
    tempBoard[move.getSrcRow()][move.getSrcCol()] = nullptr;

    // Calculate the move score
    int score = 0;
    if (isCheck(tempBoard, isWhiteTurn)) {
        score -= 1000; // Move leading to check is heavily penalized
    }
    if (isCheckmate(tempBoard, !isWhiteTurn)) {
        score += 1000; // Move leading to checkmate is highly rewarded
    }

    // Add points if the move captures an opponent's piece
    Piece* capturedPiece = board[move.getDestRow()][move.getDestCol()];
    if (capturedPiece) {
        score += getPieceValue(capturedPiece->getSymbol());
    }

    // Clean up the temporary board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete tempBoard[i][j];
        }
    }

    return score;
}

int Board::minimax(int depth, bool isWhiteTurn, int alpha, int beta) const {
    if (depth >= MAX_DEPTH) {
        return 0; // Stop at max depth
    }

    PriorityQueue<Move, MoveComparator> pq(5);  // Max size 5
    findBestMoves(isWhiteTurn, pq);

    if (pq.isEmpty()) {
        return 0;
    }

    int bestScore = (isWhiteTurn ? -100000 : 100000);
    while (!pq.isEmpty()) {
        Move move = pq.poll();
        Piece* tempBoard[8][8] = {nullptr};
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j]) {
                    tempBoard[i][j] = board[i][j]->clone();
                }
            }
        }
        tempBoard[move.getDestRow()][move.getDestCol()] = tempBoard[move.getSrcRow()][move.getSrcCol()];
        tempBoard[move.getSrcRow()][move.getSrcCol()] = nullptr;
        int score = evaluateMove(move, isWhiteTurn);

        if (isWhiteTurn) {
            bestScore = std::max(bestScore, score);
            alpha = std::max(alpha, score);
        } else {
            bestScore = std::min(bestScore, score);
            beta = std::min(beta, score);
        }

        // Clean up the temporary board
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete tempBoard[i][j];
            }
        }

        if (beta <= alpha) {
            break;  // Alpha-beta pruning
        }
    }

    return bestScore;
}

Move Board::getBestMove(bool isWhiteTurn) const {
    PriorityQueue<Move, MoveComparator> pq(5);  // Max size 5
    findBestMoves(isWhiteTurn, pq);

    if (!pq.isEmpty()) {
        return pq.poll();
    }

    throw std::runtime_error("No valid moves found");
}

bool Board::isCheck(Piece* const board[8][8], bool isWhiteTurn) const {
    // Find the king
    int kingRow = -1, kingCol = -1;
    char kingSymbol = isWhiteTurn ? 'K' : 'k';

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->getSymbol() == kingSymbol) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    if (kingRow == -1) return false; // King not found (should not happen)

    // Check if any opponent piece can move to the king's position
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->isWhitePiece() != isWhiteTurn && board[i][j]->isValidMove(i, j, kingRow, kingCol, board)) {
                return true;
            }
        }
    }

    return false;
}

bool Board::isCheckmate(Piece* const board[8][8], bool isWhiteTurn) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board[i][j];
            if (piece && piece->isWhitePiece() == isWhiteTurn) {
                for (int destRow = 0; destRow < 8; ++destRow) {
                    for (int destCol = 0; destCol < 8; ++destCol) {
                        if (piece->isValidMove(i, j, destRow, destCol, board)) {
                            Piece* tempBoard[8][8] = {nullptr};
                            for (int k = 0; k < 8; ++k) {
                                for (int l = 0; l < 8; ++l) {
                                    if (board[k][l]) {
                                        tempBoard[k][l] = board[k][l]->clone();
                                    }
                                }
                            }
                            tempBoard[destRow][destCol] = tempBoard[i][j];
                            tempBoard[i][j] = nullptr;
                            if (!isCheck(tempBoard, isWhiteTurn)) {
                                return false; // Not checkmate if there's at least one valid move
                            }
                            // Clean up the temporary board
                            for (int k = 0; k < 8; ++k) {
                                for (int l = 0; l < 8; ++l) {
                                    delete tempBoard[k][l];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return true; // Checkmate if no valid moves found
}