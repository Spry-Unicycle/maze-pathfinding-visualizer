#include "bfs.h"

using namespace std;

const int rows = 20;
const int cols = 20;

static vector<vector<bool>> visited(rows, vector<bool>(cols,false));

static vector<vector<pair<int,int>>> parent(
    rows,
    vector<pair<int,int>>(cols,{-1,-1})
);

static queue<pair<int,int>> q;

int bfsVisitedCount=0;
bool bfsRunning = false;
bool pathFound = false;

void startBFS(
    vector<vector<int>>& grid,
    pair<int,int> startpos
){
    while(!q.empty())
        q.pop();

    visited.assign(rows,vector<bool>(cols,false));

    parent.assign(
        rows,
        vector<pair<int,int>>(cols,{-1,-1})
    );

    pathFound = false;

    q.push(startpos);

    visited[startpos.first][startpos.second] = true;
    bfsVisitedCount = 1;
    bfsRunning = true;
}

void bfsStep(
    vector<vector<int>>& grid,
    pair<int,int> startpos,
    pair<int,int> endpos
){
    if(q.empty()){
        bfsRunning = false;
        return;
    }

    auto [r,c] = q.front();
    q.pop();

    if(make_pair(r,c) == endpos){

        bfsRunning = false;
        pathFound = true;

        pair<int,int> cur = endpos;

        while(cur != startpos){

            auto [pr,pc] = cur;

            if(grid[pr][pc] != 2 &&
               grid[pr][pc] != 3)
            {
                grid[pr][pc] = 5;
            }

            cur = parent[pr][pc];
        }

        return;
    }

    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};

    for(int i=0;i<4;i++){

        int nr = r + dr[i];
        int nc = c + dc[i];

        if(nr < 0 || nr >= rows ||
           nc < 0 || nc >= cols)
            continue;

        if(visited[nr][nc])
            continue;

        if(grid[nr][nc] == 1)
            continue;

        visited[nr][nc] = true;
        bfsVisitedCount++;
        parent[nr][nc] = {r,c};

        if(grid[nr][nc] != 2 &&
           grid[nr][nc] != 3)
        {
            grid[nr][nc] = 4;
        }

        q.push({nr,nc});
    }
}
void resetbfs()
{
    bfsRunning = false;
    pathFound = false;

    while(!q.empty())
        q.pop();

    visited.assign(rows, vector<bool>(cols,false));

    parent.assign(
        rows,
        vector<pair<int,int>>(cols,{-1,-1})
    );
}