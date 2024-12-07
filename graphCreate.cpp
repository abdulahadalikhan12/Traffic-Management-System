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
    Intersection *intersections; // head of the list of intersections

public:
    Graph() : intersections(nullptr) {}

    // add a new intersection
    void addIntersection(char name, int greenTime = 0)
    {
        Intersection *newIntersection = new Intersection(name, greenTime);

        // if the list is empty, the new intersection becomes the head
        if (!intersections)
        {
            intersections = newIntersection;
        }
        else
        {
            // otherwise, traverse to the end of the list and append the new intersection
            Intersection *current = intersections;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newIntersection;
        }
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
            addIntersection(from); // add intersection if not already present
            fromIntersection = findIntersection(from);
        }

        Road *newRoad = new Road(to, travelTime);

        // if there are no roads, the new road is the first one
        if (!fromIntersection->roads)
        {
            fromIntersection->roads = newRoad;
        }
        else
        {
            // otherwise, traverse to the end of the list of roads and append the new road
            Road *current = fromIntersection->roads;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newRoad;
        }
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

    void createIntersections(const string &fileName)
    {
        ifstream file(fileName);
        if (!file)
        {
            cout << "Error opening file!" << endl;
            return;
        }
        // read traffic_signals.csv
        // Intersection,GreenTime
        // A,30
        string line;
        while (getline(file, line))
        {
            char name;
            int greenTime;
            if (sscanf(line.c_str(), "%c,%d", &name, &greenTime) == 2)
            {
                addIntersection(name, greenTime);
            }
        }

        file.close();
    }

    void createNetwork(const string &fileName)
    {
        ifstream file(fileName);
        if (!file)
        {
            cout << "Error opening file!" << endl;
            return;
        }
        // read road_network.csv
        // Intersection1,Intersection2,TravelTime
        // A,B,10

        string line;
        while (getline(file, line))
        {
            char from, to;
            int travelTime;
            if (sscanf(line.c_str(), "%c,%c,%d", &from, &to, &travelTime) == 3)
            {
                addRoad(from, to, travelTime);
            }
        }

        file.close();
    }
};
