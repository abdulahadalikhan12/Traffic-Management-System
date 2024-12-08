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
    char end;

    Vehicle *next;

    Vehicle(string name, char start, char end);
    
    void printVehicle();

};

class EmergencyVehicle : public Vehicle
{
public:

    int priority;

    EmergencyVehicle(string name, char start, char end, int priority);
    void printEmergencyDetails();
};

#endif // VEHICLE_H
