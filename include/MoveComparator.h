#pragma once
#include "Move.h"

class MoveComparator {
public:
    int operator()(const Move& a, const Move& b) const;
};