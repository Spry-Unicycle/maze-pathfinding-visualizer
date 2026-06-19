#pragma once

#include <vector>
#include <queue>
#include <utility>
extern int bfsVisitedCount;
extern bool bfsRunning;
extern bool pathFound;

void startBFS(
    std::vector<std::vector<int>>& grid,
    std::pair<int,int> startpos
);

void bfsStep(
    std::vector<std::vector<int>>& grid,
    std::pair<int,int> startpos,
    std::pair<int,int> endpos
);

void resetbfs();