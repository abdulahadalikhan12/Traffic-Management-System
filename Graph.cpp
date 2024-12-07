#include "Graph.h"
#include <iostream>
#include <sstream>

Road::Road(char dest, int travelTime)
    : dest(dest), travelTime(travelTime), next(nullptr) {}

Intersection::Intersection(char name, int greenTime)
    : name(name), greenTime(greenTime), roads(nullptr), next(nullptr) {}

Graph::Graph() : intersections(nullptr) {}

void Graph::addIntersection(char name, int greenTime)
{
    Intersection *newIntersection = new Intersection(name, greenTime);

    if (!intersections)
    {
        intersections = newIntersection;
    }
    else
    {
        Intersection *current = intersections;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newIntersection;
    }
}

Intersection *Graph::findIntersection(char name)
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
    return nullptr;
}

void Graph::removeIntersection(char name)
{
    Intersection *prev = nullptr;
    Intersection *curr = intersections;

    while (curr)
    {
        if (curr->name == name)
        {
            Road *road = curr->roads;
            while (road)
            {
                Road *temp = road;
                road = road->next;
                delete temp;
            }

            Intersection *temp = intersections;
            while (temp)
            {
                Road *prevRoad = nullptr;
                Road *currRoad = temp->roads;
                while (currRoad)
                {
                    if (currRoad->dest == name)
                    {
                        if (prevRoad)
                        {
                            prevRoad->next = currRoad->next;
                        }
                        else
                        {
                            temp->roads = currRoad->next;
                        }
                        delete currRoad;
                        break;
                    }
                    prevRoad = currRoad;
                    currRoad = currRoad->next;
                }
                temp = temp->next;
            }

            if (prev)
            {
                prev->next = curr->next;
            }
            else
            {
                intersections = curr->next;
            }

            delete curr;
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    std::cout << "Intersection " << name << " not found!" << std::endl;
}

void Graph::addRoad(char from, char to, int travelTime)
{
    Intersection *fromIntersection = findIntersection(from);
    if (!fromIntersection)
    {
        addIntersection(from);
        fromIntersection = findIntersection(from);
    }

    Road *newRoad = new Road(to, travelTime);

    if (!fromIntersection->roads)
    {
        fromIntersection->roads = newRoad;
    }
    else
    {
        Road *current = fromIntersection->roads;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newRoad;
    }
}

void Graph::removeRoad(char from, char to)
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

void Graph::setGreenTime(char name, int greenTime)
{
    Intersection *intersection = findIntersection(name);
    if (intersection)
    {
        intersection->greenTime = greenTime;
    }
    else
    {
        std::cout << "Intersection not found!" << std::endl;
    }
}

void Graph::visualize()
{
    Intersection *current = intersections;
    while (current)
    {
        std::cout << "Intersection " << current->name << " (Green Time: " << current->greenTime << "s) -> ";
        Road *road = current->roads;
        while (road)
        {
            std::cout << "(" << road->dest << ", " << road->travelTime << "s) ";
            road = road->next;
        }
        std::cout << std::endl;
        current = current->next;
    }
}

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

int Graph::getIntersectionCount()
{
    int count = 0;
    Intersection *current = intersections;
    while (current)
    {
        count++;
        current = current->next;
    }
    return count;
}

int Graph::getRoadCount()
{
    int count = 0;
    Intersection *current = intersections;
    while (current)
    {
        Road *road = current->roads;
        while (road)
        {
            count++;
            road = road->next;
        }
        current = current->next;
    }
    return count;
}

Intersection *Graph::detectDeadEnd()
{
    Intersection *temp = intersections;
    while (temp)
    {
        if (!temp->roads)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

bool Graph::isNetworkConnected()
{
    if (!intersections)
    {
        return false;
    }

    Intersection *current = intersections;
    while (current)
    {
        if (!current->roads)
        {
            return false;
        }
        current = current->next;
    }
    return true;
}

Intersection *Graph::maxGreenTime()
{
    if (!intersections)
    {
        return nullptr;
    }

    Intersection *max = intersections;
    Intersection *current = intersections->next;
    while (current)
    {
        if (current->greenTime > max->greenTime)
        {
            max = current;
        }
        current = current->next;
    }
    return max;
}

Intersection *Graph::minGreenTime()
{
    if (!intersections)
    {
        return nullptr;
    }

    Intersection *min = intersections;
    Intersection *current = intersections->next;
    while (current)
    {
        if (current->greenTime < min->greenTime)
        {
            min = current;
        }
        current = current->next;
    }
    return min;
}