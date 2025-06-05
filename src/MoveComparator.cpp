#include "MoveComparator.h"

int MoveComparator::operator()(const Move& a, const Move& b) const {
    return b.getScore() - a.getScore();
}