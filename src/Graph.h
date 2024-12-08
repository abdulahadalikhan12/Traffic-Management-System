#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include "Vehicle.h"

#define MAX_INTERSECTIONS 26 // maximum number of intersections (A-Z)

class Road
{
public:
    int travelTime;
    int status; // 1 = Clear, 2 = Blocked, 3 = Under Repair
    char src;   // source intersection
    char dest;  // destination intersection
    Road *next;

    Road(char src, char dest, int travelTime);

    int getStatus();
    std::string getStatusString();
    void setStatus(int status);
};

class Intersection
{
public:
    int greenTime;       // green light time for the intersection
    int congestionLevel; // congestion level
    char name;
    bool emergencyFlag; // flag to check if emergency is triggered
    Intersection *next; // pointer to the next intersection
    Road *roads;        // linked list of outgoing roads
    Vehicle *vehicles;  // list of vehicles at this intersection

    Intersection(char name, int greenTime = 0);

    void addVehicle(Vehicle *&vehicle);
    void removeVehicle(const std::string &name);
    void printVehicles();
};

class Graph
{
private:
    Intersection *intersections[MAX_INTERSECTIONS]; // array of intersection pointers/adjacency list

public:
    Graph();

    void addIntersection(char name, int greenTime = 0);
    Intersection *findIntersection(char name);
    void addRoad(char from, char to, int travelTime);
    void visualizeNetwork();
    void visualizeSignals();
    void createIntersections(const std::string &fileName);
    void createNetwork(const std::string &fileName);
    void createVehicles(const std::string &fileName);
    void printAllVehicles();
    void dijkstra(char start, char end);
    char dijkstra(char start, char end, unsigned int n);
    void simulateRoadClosure(const std::string &fileName);
    void updateRoadStatus(char start, char end, std::string status);
    void moveVehiclesEfficiently(const std::string &vehicleName);
    void rerouteForBlocked(char start, char end);
    void BFS(char start, char end);
    void printReroutedPath(int parent[], int startIndex, int endIndex);
};

#endif // GRAPH_H
