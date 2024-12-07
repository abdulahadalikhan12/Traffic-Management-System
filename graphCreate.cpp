/*1. City Traffic Network (Graph Representation)
● Represent the city’s traffic infrastructure as a weighted, directed graph:
o Nodes: Represent intersections.
o Edges: Represent roads between intersections, with weights representing travel
time or congestion levels.
● Features:
o Support dynamic addition and removal of roads or intersections.
o Visualize the graph structure in a text-based or graphical form.*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Road
{
    char dest;      // destination intersection
    int travelTime; // travel time/congestion level for the road
    Road *next;

    Road(char dest, int travelTime = 0)
        : dest(dest), travelTime(travelTime), next(nullptr) {}
};

struct Intersection
{
    char name;
    int greenTime;
    Road *roads;        // linked list of outgoing roads (adjacency list)
    Intersection *next; // pointer to the next intersection in the list

    Intersection(char name, int greenTime = 0)
        : name(name), greenTime(greenTime), roads(nullptr), next(nullptr) {}
};

