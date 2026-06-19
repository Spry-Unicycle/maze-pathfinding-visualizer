# Maze Pathfinding Visualizer

An interactive pathfinding visualizer built with **C++** and **SFML** that allows users to design custom mazes and compare the behavior of multiple pathfinding algorithms in real time. The application visualizes node exploration, path reconstruction, and algorithm efficiency through animated traversal.

## Features

* Interactive maze creation and editing
* Start and end node placement
* Real-time visualization of:

  * Breadth-First Search (BFS)
  * Depth-First Search (DFS)
  * A* Search
* Animated node exploration
* Path reconstruction and visualization
* Visited node statistics for algorithm comparison
* Reset and rerun functionality

## Algorithms Implemented

### Breadth-First Search (BFS)

* Guarantees the shortest path in an unweighted grid
* Explores nodes level by level

### Depth-First Search (DFS)

* Explores paths deeply before backtracking
* Demonstrates non-optimal pathfinding behavior

### A* Search

* Uses Manhattan-distance heuristic
* Finds the shortest path while exploring significantly fewer nodes than BFS

## Controls

| Key             | Action                    |
| --------------- | ------------------------- |
| **W**           | Wall placement mode       |
| **S**           | Start node placement mode |
| **E**           | End node placement mode   |
| **B**           | Run BFS                   |
| **D**           | Run DFS                   |
| **A**           | Run A* Search             |
| **R**           | Reset grid                |
| **Left Click**  | Place selected object     |
| **Right Click** | Erase cell                |

## Visual Legend

| Color  | Meaning      |
| ------ | ------------ |
| White  | Empty cell   |
| Black  | Wall         |
| Green  | Start node   |
| Red    | End node     |
| Blue   | Visited node |
| Yellow | Final path   |

## Technologies Used

* C++
* SFML 3.x
* Breadth-First Search (BFS)
* Depth-First Search (DFS)
* A* Search
* STL Containers (`queue`, `stack`, `priority_queue`, `vector`)

## Learning Outcomes

This project demonstrates:

* Graph traversal algorithms
* Heuristic search techniques
* Event-driven programming
* Real-time rendering with SFML
* Interactive visualization of algorithm behavior
* Modular C++ project design

## Future Improvements

* Dijkstra's Algorithm
* Weighted terrain support
* Random maze generation
* Additional pathfinding heuristics
* Performance comparison metrics
* Improved UI and statistics dashboard
