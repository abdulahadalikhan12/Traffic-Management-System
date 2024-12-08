#include "TrafficMonitor.h"
#include <iostream>

TrafficMonitor::TrafficMonitor()
{
    // initialize all road counts to 0
    for (int i = 0; i < MAX_ROADS; i++)
    {
        roadVehicleCounts[i].vehicleCount = 0;
    }
}

// helper function to find the index of the road in the array
int TrafficMonitor::getRoadIndex(char start, char end)
{
    int index = (start - 'A') * 26 + (end - 'A');
    return index;
}

// increment vehicle count on a road
void TrafficMonitor::addVehicleToRoad(char start, char end)
{
    int index = getRoadIndex(start, end);
    roadVehicleCounts[index].vehicleCount++;
}

// decrement vehicle count on a road
void TrafficMonitor::removeVehicleFromRoad(char start, char end)
{
    int index = getRoadIndex(start, end);
    if (roadVehicleCounts[index].vehicleCount > 0)
    {
        roadVehicleCounts[index].vehicleCount--;
    }
}

// get vehicle count on a specific road
int TrafficMonitor::getVehicleCount(char start, char end)
{
    int index = getRoadIndex(start, end);
    return roadVehicleCounts[index].vehicleCount;
}

// display traffic status for all roads
void TrafficMonitor::displayTrafficStatus()
{
    for (int i = 0; i < MAX_ROADS; i++)
    {
        if (roadVehicleCounts[i].vehicleCount > 0)
        {
            std::cout << roadVehicleCounts[i].road.start << " -> "
                      << roadVehicleCounts[i].road.end << " : "
                      << roadVehicleCounts[i].vehicleCount << " vehicles" << std::endl;
        }
    }
}

// identify congested roads and reroute traffic
void TrafficMonitor::identifyCongestion(int threshold)
{
    for (int i = 0; i < MAX_ROADS; i++)
    {
        if (roadVehicleCounts[i].vehicleCount > threshold)
        {
            std::cout << "Congested road detected: "
                      << roadVehicleCounts[i].road.start << " -> "
                      << roadVehicleCounts[i].road.end << std::endl;
            // Implement rerouting logic here
        }
    }
}
