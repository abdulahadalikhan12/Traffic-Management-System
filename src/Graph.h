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
    int travelTime; // travel time/congestion level for the road
    int status; // 1 = Clear, 2 = Blocked, 3 = Under Repair
    int vehicleCount;
    char src;       // source intersection
    char dest;      // destination intersection
    bool emergencyFlag; //flag to check if energency is triggered
    Road *next;
    //Vehicle *vehicles;

    Road(char src,char dest, int travelTime);
    
    void setEmergencyFlag(bool flag);
    bool getEmergencyFlag();

    void setVehicleCount(int count);
    int getVehicleCount();

    void incrementVehicleCount();
    void decrementVehicleCount();

    int getStatus();
    std::string getStatusString();
    void setStatus(int status);

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
