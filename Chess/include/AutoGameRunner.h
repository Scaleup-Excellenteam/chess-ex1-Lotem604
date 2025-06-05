#pragma once

#include "Board.h"
#include "ThreadPool.h"
#include "Move.h"

class AutoGameRunner {
public:
    static void runAutoGame(int depth, int threshold, int numThreads, int maxPlies = 8);
};
