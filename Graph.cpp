#include "Graph.h"

Road::Road(char dest, int travelTime)
    : dest(dest), travelTime(travelTime), next(nullptr) {}

Intersection::Intersection(char name, int greenTime)
    : name(name), greenTime(greenTime), roads(nullptr), next(nullptr) {}

Graph::Graph()
{
    for (int i = 0; i < MAX_INTERSECTIONS; ++i)
    {
        intersections[i] = nullptr;
    }
}

// add a new intersection
void Graph::addIntersection(char name, int greenTime)
{
    int index = name - 'A'; // Map 'A' to 0, 'B' to 1, ..., 'Z' to 25
    if (index < 0 || index >= MAX_INTERSECTIONS)
    {
        std::cout << "Invalid intersection name!" << std::endl;
        return;
    }

    if (intersections[index] == nullptr)
    {
        intersections[index] = new Intersection(name, greenTime);
    }
}

// find an intersection by its name
Intersection *Graph::findIntersection(char name)
{
    int index = name - 'A'; // Map 'A' to 0, 'B' to 1, ..., 'Z' to 25
    if (index < 0 || index >= MAX_INTERSECTIONS)
    {
        return nullptr;
    }
    return intersections[index];
}

// add a road between two intersections
void Graph::addRoad(char from, char to, int travelTime)
{
    Intersection *fromIntersection = findIntersection(from);
    if (!fromIntersection)
    {
        addIntersection(from);
        fromIntersection = findIntersection(from);
    }

    Road *newRoad = new Road(to, travelTime);
    newRoad->next = fromIntersection->roads;
    fromIntersection->roads = newRoad;
}

// Visualize the city traffic network (intersection names and their roads)
void Graph::visualizeNetwork()
{
    for (int i = 0; i < MAX_INTERSECTIONS; ++i)
    {
        if (intersections[i])
        {
            std::cout << intersections[i]->name << " -> ";
            Road *road = intersections[i]->roads;
            while (road)
            {
                std::cout << "(" << road->dest << ", " << road->travelTime << "s) ";
                road = road->next;
            }
            std::cout << std::endl;
        }
    }
}

void Graph::visualizeSignals()
{
    for( int i = 0 ; i < MAX_INTERSECTIONS; i++)
    {
        if(intersections[i])
        {
            std::cout << intersections[i]->name << " -> " << intersections[i]->greenTime << "s" << std::endl;
        }
    }
}

// Create intersections from a CSV file
void Graph::createIntersections(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
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

// Create roads between intersections from a CSV file
void Graph::createNetwork(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
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
