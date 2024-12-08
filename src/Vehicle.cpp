#include "Vehicle.h"

Vehicle::Vehicle(string name, char start, char end)
{
    this->name = name;
    this->start = start;
    this->end = end;
    this->next = nullptr;
}

// print details of the vehicle
void Vehicle::printVehicle()
{
    cout << "Vehicle Name: " << name << endl;
    cout << "Start: " << start << endl;
    cout << "End: " << end << endl;
}

// constructor for EmergencyVehicle
EmergencyVehicle::EmergencyVehicle(string name, char start, char end, int priority) : Vehicle(name, start, end), priority(priority) {}

// print details of the emergency vehicle
void EmergencyVehicle::printEmergencyDetails()
{
    printVehicle();
    cout << "Priority: " << priority << endl;
}
