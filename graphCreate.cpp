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

class Graph
{
    Intersection *intersections; //head of the list of intersections

public:
    Graph() : intersections(nullptr) {}

    // add a new intersection
    void addIntersection(char name, int greenTime = 0)
    {
        Intersection *newIntersection = new Intersection(name, greenTime);
        newIntersection->next = intersections;
        intersections = newIntersection;
    }

    // find an intersection by its name
    Intersection *findIntersection(char name)
    {
        Intersection *current = intersections;
        while (current)
        {
            if (current->name == name)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Intersection not found
    }

    // add a road between two intersections
    void addRoad(char from, char to, int travelTime)
    {
        Intersection *fromIntersection = findIntersection(from);
        if (!fromIntersection)
        {
            addIntersection(from); // Add intersection if not already present
            fromIntersection = findIntersection(from);
        }

        // add the road to the adjacency list (linked list of roads)
        Road *newRoad = new Road(to, travelTime);
        newRoad->next = fromIntersection->roads;
        fromIntersection->roads = newRoad;
    }

    // remove a road between two intersections
    void removeRoad(char from, char to)
    {
        Intersection *fromIntersection = findIntersection(from);
        if (!fromIntersection)
            return;

        Road *prev = nullptr;
        Road *curr = fromIntersection->roads;
        while (curr)
        {
            if (curr->dest == to)
            {
                if (prev)
                {
                    prev->next = curr->next;
                }
                else
                {
                    fromIntersection->roads = curr->next;
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    // set the green time for a specific intersection
    void setGreenTime(char name, int greenTime)
    {
        Intersection *intersection = findIntersection(name);
        if (intersection)
        {
            intersection->greenTime = greenTime;
        }
        else
        {
            cout << "Intersection not found!" << endl;
        }
    }

    // visualize the graph (print all intersections and their roads)
    void visualize()
    {
        Intersection *current = intersections;
        while (current)
        {
            cout << "Intersection " << current->name << " (Green Time: " << current->greenTime << "s) -> ";
            Road *road = current->roads;
            while (road)
            {
                cout << "(" << road->dest << ", " << road->travelTime << "s) ";
                road = road->next;
            }
            cout << endl;
            current = current->next;
        }
    }
};
