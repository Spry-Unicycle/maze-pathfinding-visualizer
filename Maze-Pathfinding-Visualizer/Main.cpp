#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "bfs.h"
#include "dfs.h"
#include "astar.h"
using namespace std;

const int rows=20;
const int cols=20;
const int cell_size=30;
vector<vector<int>> grid(rows,vector<int> (cols,0));

pair<int,int> startpos={-1,-1};
pair<int,int> endpos={-1,-1};
string resultMessage = "";
int currentmode=1;
bool runBFS=false;
bool runDFS=false;
bool runAStar=false;



int main(){
    sf::RenderWindow window(
        sf::VideoMode({800, 800}),
        "Maze Solver"
    );

    sf::Font font;

    if(!font.openFromFile("arial.ttf"))
    {
        return -1;
    }

    sf::Text resultText(font);

    resultText.setCharacterSize(12);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(sf::Vector2f(650.f, 50.f));

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
                if(key->scancode == sf::Keyboard::Scancode::D)runDFS = true;
                if(key->scancode == sf::Keyboard::Scancode::A)runAStar = true;
                if (key->scancode == sf::Keyboard::Scancode::R){
                    for(int r=0;r<rows;r++){
                        for(int c=0;c<cols;c++){
                            if(grid[r][c] != 1)grid[r][c] = 0;
                        }
                    }
                    startpos = {-1,-1};
                    endpos = {-1,-1};
                    
                    resetbfs();
                    resetDFS();
                    resetAStar();

                }
            }
        }
        if(runDFS){
            if(startpos.first != -1 &&
            endpos.first != -1){
                for(int r=0;r<rows;r++){
                    for(int c=0;c<cols;c++){
                        if(grid[r][c]==4 ||
                        grid[r][c]==5){
                            grid[r][c]=0;
                        }
                    }
                }
                startDFS(grid,startpos);
            }

            runDFS = false;
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
                startBFS(grid, startpos);
            }
            runBFS = false;
        }

        if(runAStar)
        {
            if(startpos.first!=-1 &&
            endpos.first!=-1)
            {
                for(int r=0;r<rows;r++)
                {
                    for(int c=0;c<cols;c++)
                    {
                        if(grid[r][c]==4 ||
                        grid[r][c]==5)
                            grid[r][c]=0;
                    }
                }

                startAStar(
                    grid,
                    startpos,
                    endpos
                );
            }

            runAStar = false;
        }

        if(bfsRunning&&bfsClock.getElapsedTime().asMilliseconds() > 30){
            bfsStep(grid, startpos, endpos);
            bfsClock.restart();
        }
        if(dfsRunning &&bfsClock.getElapsedTime().asMilliseconds() > 30){
            dfsStep(grid,startpos,endpos);
            bfsClock.restart();
        }   
        if(astarRunning &&bfsClock.getElapsedTime().asMilliseconds() > 30){
            astarStep(
                grid,
                startpos,
                endpos
            );

            bfsClock.restart();
        }
        if(astarFound)
        {
            resultMessage =
                "A*\nNodes Visited: " +
                to_string(astarVisitedCount);

            astarFound = false;
        }
        if(pathFound)
        {
            resultMessage =
                "BFS\nNodes Visited: " +
                to_string(bfsVisitedCount);

            pathFound = false;
        }
        if(dfsFound)
        {
            resultMessage =
                "DFS\nNodes Visited: " +
                to_string(dfsVisitedCount);

            dfsFound = false;
        }


        if(!bfsRunning&&!dfsRunning&&!astarRunning){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                auto mouse=sf::Mouse::getPosition(window);
                int col=(mouse.x-100)/cell_size;
                int row=(mouse.y-100)/cell_size;
                if(row>=0 && row<rows && col>=0 && col<cols){
                    if(currentmode==1){
                        if(make_pair(row,col)==startpos)startpos={-1,-1};
                        if(make_pair(row,col)==endpos)endpos={-1,-1};
                        grid[row][col]=1;
                    }
                    if(currentmode==2){
                        if(startpos.first!=-1)grid[startpos.first][startpos.second]=0;
                        if(make_pair(row,col)==endpos) endpos={-1,-1};
                        startpos={row,col};
                        grid[row][col]=2;
                    }
                    if(currentmode==3){
                        if(endpos.first!=-1)grid[endpos.first][endpos.second]=0;
                        if(make_pair(row,col)==startpos)startpos={-1,-1};
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
                    if(make_pair(row,col)==startpos)startpos={-1,-1};
                    if(make_pair(row,col)==endpos)endpos={-1,-1};

                    grid[row][col]=0;
                }
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
        resultText.setString(resultMessage);
        window.draw(resultText);
        window.display();
    }

    return 0;
}