#include "astar.h"
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

const int rows = 20;
const int cols = 20;

struct Node
{
    int f;
    int g;
    int r;
    int c;

    bool operator<(const Node& other) const
    {
        return f > other.f;
    }
};

static priority_queue<Node> pq;

static vector<vector<bool>> visited(
    rows,
    vector<bool>(cols,false)
);

static vector<vector<pair<int,int>>> parent(
    rows,
    vector<pair<int,int>>(cols,{-1,-1})
);
int astarVisitedCount = 0;
bool astarRunning = false;
bool astarFound = false;

int heuristic(int r,
    int c,
    int er,
    int ec
)
{
    return abs(r-er) + abs(c-ec);
}

void startAStar(
    vector<vector<int>>& grid,
    pair<int,int> startpos,
    pair<int,int> endpos
)
{
    while(!pq.empty())
        pq.pop();

    visited.assign(
        rows,
        vector<bool>(cols,false)
    );

    parent.assign(
        rows,
        vector<pair<int,int>>(cols,{-1,-1})
    );

    int h = heuristic(
        startpos.first,
        startpos.second,
        endpos.first,
        endpos.second
    );

    pq.push({
        h,
        0,
        startpos.first,
        startpos.second
    });
    astarVisitedCount=1;
    astarRunning = true;
    astarFound = false;
}

void astarStep(
    vector<vector<int>>& grid,
    pair<int,int> startpos,
    pair<int,int> endpos
)
{
    if(pq.empty())
    {
        astarRunning = false;
        return;
    }

    Node cur = pq.top();
    pq.pop();

    int r = cur.r;
    int c = cur.c;

    if(visited[r][c])
        return;

    visited[r][c] = true;
    astarVisitedCount++;
        if(make_pair(r,c) == endpos)
    {
        astarRunning = false;
        astarFound = true;

        pair<int,int> curNode = endpos;

        while(curNode != startpos)
        {
            auto [pr,pc] = curNode;

            if(grid[pr][pc] != 2 &&
               grid[pr][pc] != 3)
            {
                grid[pr][pc] = 5;
            }

            curNode = parent[pr][pc];
        }

        return;
    }
        int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};

    for(int i=0;i<4;i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if(nr < 0 || nr >= rows ||
           nc < 0 || nc >= cols)
            continue;

        if(grid[nr][nc] == 1)
            continue;

        if(visited[nr][nc])
            continue;

        int newG = cur.g + 1;

        int h = heuristic(
            nr,
            nc,
            endpos.first,
            endpos.second
        );

        int f = newG + h;

        parent[nr][nc] = {r,c};

        if(grid[nr][nc] != 2 &&
           grid[nr][nc] != 3)
        {
            grid[nr][nc] = 4;
        }

        pq.push({
            f,
            newG,
            nr,
            nc
        });
    }
}
void resetAStar()
{
    while(!pq.empty())
        pq.pop();

    astarRunning = false;
    astarFound = false;
}