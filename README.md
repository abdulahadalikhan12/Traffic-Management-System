---

# Traffic Simulation System

## Overview
The **Traffic Simulation System** is a program designed to simulate the dynamics of a city's traffic network, including intersections, roads, and vehicles. It allows for the creation and management of intersections and roads, vehicle movement, and rerouting based on traffic conditions. The system integrates several algorithms for pathfinding and traffic management, such as **Dijkstra’s Algorithm**, **A\***, **BFS**, and **DFS**.

## Features
- **Intersections & Roads**: Create and manage intersections and roads, including adding roads between intersections with travel times.
- **Vehicle Movement**: Add vehicles to intersections and simulate their movement across the traffic network.
- **Pathfinding**: Use **Dijkstra’s Algorithm**, **A\***, **DFS**, and **BFS** to find optimal routes and paths between intersections.
- **Road Closure Simulation**: Simulate road closures and repairs, and reroute vehicles accordingly.
- **Traffic Network Visualization**: Visualize the traffic network, showing intersections, roads, their statuses, and congestion levels.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Algorithms](#algorithms)
  - [Dijkstra’s Algorithm](#dijkstras-algorithm)
  - [A\* Algorithm](#a-algorithm)
  - [DFS](#depth-first-search-dfs)
  - [BFS](#breadth-first-search-bfs)
- [File Structure](#file-structure)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Prerequisites
- **C++11 or later** compiler (e.g., `g++`)
- **CMake** (optional, for building the project with CMake)
- **Make** (optional, if using a `Makefile`)

### Steps to Set Up
1. Clone the repository:
    ```bash
    git clone https://github.com/Mnb-0/Smart-Traffic-Management-System.git
    cd Smart-Traffic-Management-System
    ```

2. Compile the project:
    - If you're using a **Makefile**:
      ```bash
      make
      ```

    - Or, using **CMake** (if you have a `CMakeLists.txt` file):
      ```bash
      mkdir build
      cd build
      cmake ..
      make
      ```

3. Run the program:
    ```bash
    ./traffic_simulator
    ```

## Usage

After setting up the project, you can run the traffic simulation by using the main program. The system will create intersections, roads, and vehicles from CSV files.

### Example of Creating an Intersection:
```cpp
graph.addIntersection('A', 30);  // Add intersection 'A' with a green light duration of 30 seconds
```

### Example of Adding a Road:
```cpp
graph.addRoad('A', 'B', 10);  // Add a road from 'A' to 'B' with a travel time of 10 seconds
```

### Example of Moving a Vehicle:
```cpp
graph.moveVehicleToNewIntersection("V1", 'B');  // Move vehicle "V1" to intersection 'B'
```

### Example of Simulating Road Closures:
```cpp
graph.simulateRoadClosure("roadClosures.csv");  // Simulate road closures based on the data in the CSV file
```

## Algorithms

### Dijkstra’s Algorithm
**Dijkstra's Algorithm** is used to find the shortest path between two intersections where roads have specific weights (travel times). The algorithm iteratively selects the closest unvisited intersection and updates the distances to its neighbors. It uses a **MinHeap** to efficiently select the next intersection with the shortest distance.

### A\* Algorithm
**A\*** is an enhanced version of Dijkstra's algorithm that uses a heuristic to prioritize intersections that are likely closer to the destination. This makes the algorithm more efficient in complex networks, reducing travel time by guiding the search based on both actual distance and estimated cost to reach the destination.

### Depth-First Search (DFS)
**DFS** explores as far as possible down a branch before backtracking. This algorithm is used to explore all possible routes between two intersections. It's helpful for discovering all potential paths in the traffic network, even though it is not necessarily the most efficient for finding the shortest route.

### Breadth-First Search (BFS)
**BFS** is used to find the shortest path in an unweighted graph or when all roads have the same weight. BFS explores all neighbors at the present depth level before moving on to the next level, making it ideal for determining the minimum number of intersections to cross between two points.

## File Structure
Here is an overview of the file structure:

```
src/
├── Graph.h            # Header for the Graph class (contains intersection and road management)
├── Graph.cpp          # Implementation of the Graph class
├── MinHeap.h          # Header for the MinHeap class (template-based)
├── MinHeap.cpp        # Implementation of the MinHeap class
├── Queue.h            # Header for the Queue class
├── Queue.cpp          # Implementation of the Queue class
├── TrafficMonitor.h   # Header for TrafficMonitor class (handles congestion and road status)
├── TrafficMonitor.cpp # Implementation of TrafficMonitor class
├── Vehicle.h          # Header for the Vehicle class
├── Vehicle.cpp        # Implementation of the Vehicle class
├── main.cpp           # Entry point for the simulation program
```

### Graph Class
The **Graph** class represents the traffic network, managing intersections, roads, vehicles, and performing traffic simulations, including pathfinding with algorithms like **Dijkstra’s**, **A\***, **DFS**, and **BFS**.

### MinHeap (Template)
The **MinHeap** class implements a heap data structure that supports efficient extraction of the minimum element. This is used in **Dijkstra’s Algorithm** and **A\*** for selecting the closest intersection based on distance.

### Queue Class
The **Queue** class is used to manage the breadth-first search (BFS) traversal, storing intersections to explore in the BFS algorithm.

### TrafficMonitor Class
The **TrafficMonitor** class tracks congestion levels at each intersection and manages road statuses, such as clear, blocked, or under repair. It also triggers rerouting when necessary.

### Vehicle Class
The **Vehicle** class represents a vehicle in the simulation. It stores the vehicle's current intersection, destination, and handles the movement of the vehicle between intersections.

### main.cpp
`main.cpp` is the entry point for the simulation. It initializes the **Graph**, **MinHeap**, **Queue**, **TrafficMonitor**, and **Vehicle** objects, and orchestrates the traffic simulation by invoking various algorithms and managing the traffic flow.

## Contributing

1. Fork the repository.
2. Create your feature branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
