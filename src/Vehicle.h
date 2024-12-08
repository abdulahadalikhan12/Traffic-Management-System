#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
protected:
    string name;
    char start;
    char end;

public:
    Vehicle(string name, char start, char end);
    void printVehicle();
};

class EmergencyVehicle : public Vehicle
{
    int priority;

public:
    EmergencyVehicle(string name, char start, char end, int priority);
    void printEmergencyDetails();
};

#endif // VEHICLE_H
