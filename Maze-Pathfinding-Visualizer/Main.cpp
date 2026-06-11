#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace std;

const int rows=20;
const int cols=20;
const int cell_size=30;
vector<vector<int>> grid(rows,vector<int> (cols,0));

pair<int,int> startpos={-1,-1};
pair<int,int> endpos={-1,-1};

vector<vector<bool>> visited(rows,vector<bool>(cols, false));
vector<vector<pair<int,int>>> parent(rows,vector<pair<int,int>>(cols,{-1,-1}));
queue<pair<int,int>> q;

bool bfsRunning = false;
bool pathFound = false;

int currentmode=1;
bool runBFS=false;

void startBFS()
{
    while(!q.empty())q.pop();

    visited.assign(rows,vector<bool>(cols,false));

    parent.assign(rows,vector<pair<int,int>>(cols,{-1,-1})
    );

    q.push(startpos);
    visited[startpos.first][startpos.second] = true;

    bfsRunning = true;
}

void bfsStep()
{
    if(q.empty()){
        bfsRunning = false;
        return;
    }

    auto [r,c] =q.front();
    q.pop();

    if(make_pair(r,c) == endpos){
        bfsRunning = false;
        pathFound = true;
        pair<int,int> cur = endpos;
        while(cur != startpos){
            auto [pr, pc] = cur;
            if(grid[pr][pc] != 2 &&grid[pr][pc] != 3)grid[pr][pc] = 5;
            cur = parent[pr][pc];
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

        if(visited[nr][nc])
            continue;

        if(grid[nr][nc] == 1)
            continue;

        visited[nr][nc] = true;

        parent[nr][nc] = {r,c};

        if(grid[nr][nc] != 3&&grid[nr][nc]!=2)
            grid[nr][nc] = 4;

        q.push({nr,nc});
    }
}

int main(){
    sf::RenderWindow window(
        sf::VideoMode({800, 800}),
        "Maze Solver"
    );
    window.setFramerateLimit(60);
    sf::Clock bfsClock;
    while (window.isOpen())
    {
        while (const auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()){
                if (key->scancode == sf::Keyboard::Scancode::W)currentmode = 1;
                if (key->scancode == sf::Keyboard::Scancode::S)currentmode = 2;
                if (key->scancode == sf::Keyboard::Scancode::E)currentmode = 3;
                if (key->scancode == sf::Keyboard::Scancode::B)runBFS=true;
                if (key->scancode == sf::Keyboard::Scancode::R){
                    for(int r=0;r<rows;r++){
                        for(int c=0;c<cols;c++){
                            if(grid[r][c] != 1)grid[r][c] = 0;
                        }
                    }
                    startpos = {-1,-1};
                    endpos = {-1,-1};

                    bfsRunning = false;
                    pathFound = false;

                    while(!q.empty())q.pop();
                }
            }
        }
        

        if(runBFS){
            if(startpos.first != -1 &&endpos.first != -1){
                for(int r=0;r<rows;r++){
                    for(int c=0;c<cols;c++){
                        if(grid[r][c] == 4 ||grid[r][c] == 5){
                            grid[r][c] = 0;
                        }
                    }
                }
                startBFS();
            }
            runBFS = false;
        }

        if(bfsRunning&&bfsClock.getElapsedTime().asMilliseconds() > 30){
            bfsStep();
            bfsClock.restart();
        }   


        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            auto mouse=sf::Mouse::getPosition(window);
            int col=(mouse.x-100)/cell_size;
            int row=(mouse.y-100)/cell_size;
            if(row>=0 && row<rows && col>=0 && col<cols){
                if(currentmode== 1)grid[row][col] = 1;
                if(currentmode==2){
                    if(startpos.first!=-1){
                        grid[startpos.first][startpos.second]=0;
                    }
                    startpos={row,col};
                    grid[row][col]=2;
                }
                if(currentmode==3){
                    if(endpos.first!=-1){
                        grid[endpos.first][endpos.second]=0;
                    }
                    endpos={row,col};
                    grid[row][col]=3;
                }
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
            auto mouse=sf::Mouse::getPosition(window);
            int col=(mouse.x-100)/cell_size;
            int row=(mouse.y-100)/cell_size;
            if(row>=0 && row<rows && col>=0 && col<cols){
                grid[row][col]=0;
            }
        }

        window.clear();
        for(int r = 0; r < rows; r++){   
            for(int c = 0; c <cols; c++){
                sf::RectangleShape cell(
                    sf::Vector2f(
                        cell_size - 1,
                        cell_size - 1
                    )
                );
                cell.setPosition(
                    sf::Vector2f(
                        100+c * cell_size,
                        100+r * cell_size
                    )
                );
                if(grid[r][c]==0){
                    cell.setFillColor(sf::Color::White);
                }
                if(grid[r][c]==1){
                    cell.setFillColor(sf::Color::Black);
                }
                if(grid[r][c]==2){
                    cell.setFillColor(sf::Color::Green);
                }
                if(grid[r][c]==3){
                    cell.setFillColor(sf::Color::Red);
                }
                if(grid[r][c]==4){
                    cell.setFillColor(sf::Color::Blue);
                }
                if(grid[r][c]==5){
                    cell.setFillColor(sf::Color::Yellow);
                }
                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}