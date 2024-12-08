#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include "Vehicle.h"

#define MAX_INTERSECTIONS 26 // maximum number of intersections (A-Z)

// Class representing a Road between two intersections
class Road
{
public:
    int travelTime; // time taken to travel the road
    int status;     // road status: 1 = Clear, 2 = Blocked, 3 = Under Repair
    char src;       // source intersection
    char dest;      // destination intersection
    Road *next;     // pointer to the next road

    Road(char src, char dest, int travelTime);

    int getStatus();
    std::string getStatusString();
    void setStatus(int status);
};

// Class representing an Intersection in the graph
class Intersection
{
public:
    int greenTime;       // green light time for the intersection
    int congestionLevel; // current congestion level
    char name;           // name of the intersection
    bool emergencyFlag;  // flag to indicate if an emergency is triggered
    Intersection *next;  // pointer to the next intersection
    Road *roads;         // linked list of outgoing roads
    Vehicle *vehicles;   // list of vehicles at this intersection

    Intersection(char name, int greenTime = 0);

    void addVehicle(Vehicle *&vehicle);
    void removeVehicle(const std::string &name);
    void printVehicles();
    void incrementCongestionLevel();
    void decrementCongestionLevel();
};

// Graph class representing the road network
class Graph
{
private:
    Intersection *intersections[MAX_INTERSECTIONS]; // adjacency list for intersections

public:
    Graph();

    // Intersection management
    Intersection *findIntersection(char name);
    void addIntersection(char name, int greenTime = 0);

    // Road management
    void addRoad(char from, char to, int travelTime);
    void updateRoadStatus(char start, char end, std::string status);
    void blockRoad(char start, char end);
    bool simulateRoadClosure(const std::string &fileName);
    void printBlockedRoads();

    // Visualization
    void visualizeNetwork();
    void visualizeSignals();

    // Vehicle management
    bool createVehicles(const std::string &fileName);
    void printAllVehicles();
    void moveVehiclesEfficiently(const std::string &vehicleName);
    void moveVehicleToNewIntersection(const std::string &vehicleName, char newIntersection);

    // File-based network creation
    bool createIntersections(const std::string &fileName);
    bool createNetwork(const std::string &fileName);

    // Routing algorithms
    void dijkstra(char start, char end);
    char dijkstra(char start, char end, unsigned int n); // Overloaded function
    void BFS(char start, char end);
    void aStar(char start, char end);

    // Rerouting and pathfinding
    void rerouteForBlocked(char start, char end);
    void rerouteNetwork();
    void printReroutedPath(int parent[], int startIndex, int endIndex);
    void findAllRoutes(char start, char end);
    void dfs(Intersection *current, char end, char currentPath[], int pathIndex, bool visited[], char allPaths[][100], int &pathCount);

};

#endif // GRAPH_H
