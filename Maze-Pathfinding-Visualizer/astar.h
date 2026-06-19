#pragma once

#include <vector>
#include <utility>
extern int astarVisitedCount;
extern bool astarRunning;
extern bool astarFound;

void startAStar(
    std::vector<std::vector<int>>& grid,
    std::pair<int,int> startpos,
    std::pair<int,int> endpos
);

void astarStep(
    std::vector<std::vector<int>>& grid,
    std::pair<int,int> startpos,
    std::pair<int,int> endpos
);

void resetAStar();