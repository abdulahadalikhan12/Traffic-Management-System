#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <climits>
#include <string>

#define MAX_INTERSECTIONS 26 // maximum number of intersections (A-Z)

class Road
{
public:
    char dest;      // destination intersection
    int travelTime; // travel time/congestion level for the road
    Road *next;
    int status; // 1 = Clear, 2 = Blocked, 3 = Under Repair

    Road(char dest, int travelTime);
    
};

class Intersection
{
public:
    char name;
    int greenTime;      // green light time for the intersection
    Road *roads;        // linked list of outgoing roads
    Intersection *next; // pointer to the next intersection

    Intersection(char name, int greenTime = 0);
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
    void dijkstra(char start, char end);
    void simulateRoadClosure(const std::string &fileName);
    void updateRoadStatus(char start, char end, std::string status);
};

#endif // GRAPH_H
