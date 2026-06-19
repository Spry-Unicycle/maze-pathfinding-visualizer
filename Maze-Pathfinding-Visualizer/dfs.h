#pragma once

#include <vector>
#include <utility>
extern int dfsVisitedCount;
extern bool dfsRunning;
extern bool dfsFound;

void startDFS(
    std::vector<std::vector<int>>& grid,
    std::pair<int,int> startpos
);

void dfsStep(
    std::vector<std::vector<int>>& grid,
    std::pair<int,int> startpos,
    std::pair<int,int> endpos
);

void resetDFS();