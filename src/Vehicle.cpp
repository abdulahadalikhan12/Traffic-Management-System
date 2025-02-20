#include "Vehicle.h"

// constructor for Vehicle
Vehicle::Vehicle(string name, char start, char end)
{
    this->name = name;
    this->start = this->current = start;
    this->end = end;
    this->next = nullptr;
}

// print details of the vehicle
void Vehicle::printVehicle()
{
    cout << "Vehicle Name: " << name << endl;
    cout << "Start: " << start << endl;
    cout << "Current: " << current << endl;
    cout << "End: " << end << endl;
}

// print the current location of the vehicle
void Vehicle::printCurrent()
{
    cout << "Current: " << current << endl;
}

// constructor for EmergencyVehicle
EmergencyVehicle::EmergencyVehicle(string name, char start, char end, int priority) : Vehicle(name, start, end), priority(priority) {}

// constructor for EmergencyVehicle
EmergencyVehicle::EmergencyVehicle(Vehicle *vehicle, int priority) : Vehicle(vehicle->name, vehicle->start, vehicle->end), priority(priority) {}

// set the priority of the emergency vehicle
void EmergencyVehicle::setPriority(int priority)
{
    this->priority = priority;
}

// get the priority of the emergency vehicle
int EmergencyVehicle::getPriority()
{
    return priority;
}

// print details of the emergency vehicle
void EmergencyVehicle::printEmergencyDetails()
{
    printVehicle();
    cout << "Priority: " << priority << endl;
}
