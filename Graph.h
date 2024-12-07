#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <fstream>

struct Road
{
    char dest;      // destination intersection
    int travelTime; // travel time/congestion level for the road
    Road *next;

    Road(char dest, int travelTime = 0);
};

struct Intersection
{
    char name;
    int greenTime;
    Road *roads;        // linked list of outgoing roads (adjacency list)
    Intersection *next; // pointer to the next intersection in the list

    Intersection(char name, int greenTime = 0);
};

class Graph
{
    Intersection *intersections; // head of the list of intersections

public:
    Graph();

    // add a new intersection
    void addIntersection(char name, int greenTime = 0);

    // find an intersection by its name
    Intersection *findIntersection(char name);

    // remove an intersection by its name
    void removeIntersection(char name);

    // add a road between two intersections
    void addRoad(char from, char to, int travelTime);

    // remove a road between two intersections
    void removeRoad(char from, char to);

    // set the green time for a specific intersection
    void setGreenTime(char name, int greenTime);

    // visualize the graph (print all intersections and their roads)
    void visualize();

    void createIntersections(const std::string &fileName);
    void createNetwork(const std::string &fileName);

    int getIntersectionCount();
    int getRoadCount();

    // detect dead ends in the network
    Intersection *detectDeadEnd();

    // check if the network is connected
    bool isNetworkConnected();

    // find the intersection with max green time
    Intersection *maxGreenTime();

    // find the intersection with min green time
    Intersection *minGreenTime();
};

#endif