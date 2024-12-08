#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
public:
    string name;
    char start;
    char current;
    char end;

    Vehicle *next;

    Vehicle(string name, char start, char end);
    
    void printVehicle();
    void printCurrent();

};

class EmergencyVehicle : public Vehicle
{
public:

    int priority;

    EmergencyVehicle(string name, char start, char end, int priority = 0);
    EmergencyVehicle(Vehicle *vehicle, int priority = 0);

    void setPriority(int priority);
    int getPriority();

    void printEmergencyDetails();
};

#endif // VEHICLE_H
