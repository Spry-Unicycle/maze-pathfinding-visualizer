#include "dfs.h"

#include <stack>
#include <vector>

using namespace std;

const int rows = 20;
const int cols = 20;

static stack<pair<int,int>> st;

static vector<vector<bool>> visited(
    rows,
    vector<bool>(cols,false)
);

static vector<vector<pair<int,int>>> parent(
    rows,
    vector<pair<int,int>>(cols,{-1,-1})
);
int dfsVisitedCount = 0;
bool dfsRunning = false;
bool dfsFound = false;

void startDFS(
    vector<vector<int>>& grid,
    pair<int,int> startpos
){
    while(!st.empty())
        st.pop();

    visited.assign(
        rows,
        vector<bool>(cols,false)
    );

    parent.assign(
        rows,
        vector<pair<int,int>>(cols,{-1,-1})
    );

    dfsFound = false;

    st.push(startpos);

    visited[startpos.first][startpos.second] = true;
    dfsVisitedCount=1;
    dfsRunning = true;
}

void dfsStep(
    vector<vector<int>>& grid,
    pair<int,int> startpos,
    pair<int,int> endpos
){
    if(st.empty()){
        dfsRunning = false;
        return;
    }

    auto [r,c] = st.top();
    st.pop();

    if(make_pair(r,c) == endpos){

        dfsRunning = false;
        dfsFound = true;

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

    for(int i=3;i>=0;i--)
    {
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
        dfsVisitedCount++;
        parent[nr][nc] = {r,c};

        if(grid[nr][nc] != 2 &&
           grid[nr][nc] != 3)
        {
            grid[nr][nc] = 4;
        }

        st.push({nr,nc});
    }
}

void resetDFS()
{
    while(!st.empty())
        st.pop();

    dfsRunning = false;
    dfsFound = false;

    visited.assign(
        rows,
        vector<bool>(cols,false)
    );

    parent.assign(
        rows,
        vector<pair<int,int>>(cols,{-1,-1})
    );
}