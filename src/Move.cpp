#include "Move.h"
#include <sstream>

std::string Move::toString() const {
    std::stringstream ss;
    ss << pieceSymbol << ": " << char('a' + srcRow) << (srcCol + 1) << " -> " << char('a' + destRow) << (destCol + 1);
    return ss.str();
}

int Move::getScore() const {
    return score;
}

void Move::setScore(int newScore) {
    score = newScore;
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.toString();
    return os;
}