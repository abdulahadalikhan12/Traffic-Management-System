#ifndef TRAFFICMONITOR_H
#define TRAFFICMONITOR_H

class TrafficMonitor
{
private:
    struct RoadKey
    {
        char start;
        char end;
        RoadKey() : start('\0'), end('\0') {}
        RoadKey(char s, char e) : start(s), end(e) {}

        bool operator==(const RoadKey &other) const
        {
            return (start == other.start && end == other.end);
        }
    };

    struct RoadVehicleCount
    {
        RoadKey road;
        int vehicleCount;
        RoadVehicleCount() : vehicleCount(0) {}
    };

    static const int MAX_ROADS = 26 * 26;          // Maximum number of roads (A-Z to A-Z)
    RoadVehicleCount roadVehicleCounts[MAX_ROADS]; // Array to store vehicle counts for each road

public:
    TrafficMonitor(); // constructor to initialize the traffic monitor

    // helper function to find the index of the road in the array
    int getRoadIndex(char start, char end);

    // increment vehicle count on a road
    void addVehicleToRoad(char start, char end);

    // decrement vehicle count on a road
    void removeVehicleFromRoad(char start, char end);

    // get vehicle count on a specific road
    int getVehicleCount(char start, char end);

    // display traffic status for all roads
    void displayTrafficStatus();

    // identify congested roads and reroute traffic
    void identifyCongestion(int threshold);
};

#endif // TRAFFICMONITOR_H
