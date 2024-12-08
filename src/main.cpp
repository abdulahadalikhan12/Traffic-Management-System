#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "../src/Graph.h"
#include "../src/TrafficMonitor.h"
#include "../src/Utility.h"
using namespace std;

Graph graph;
TrafficMonitor monitor;

int main()
{
    int choice = 0;

    loadData();

    while (choice != 9)
    {
        mainMenu();
        choice = getValidChoice();

        switch (choice)
        {
        case 1:
            // display the network
            cout << "Displaying City Traffic Network...\n";
            graph.visualizeNetwork();
            break;
        case 2:
            // display traffic signal status
            cout << "Displaying Traffic Signal Status...\n";
            graph.visualizeSignals();
            break;
        case 3:
            // display congestion status
            cout << "Displaying Congestion Status...\n";
            monitor.displayTrafficStatus();
            break;
        case 4:
            // display blocked roads
            cout << "Displaying Blocked Roads...\n";
            graph.printBlockedRoads();
            break;
        case 5:
            // handle emergency vehicle routing
            cout << "Handling emergency vehicle routing...\n";
            // graph.handleEmergencyVehicle(); // Uncomment once implemented
            break;
        case 6:
            // block a road due to an accident
            handleBlockedRoad();
            break;
        case 7:
            // simulate vehicle routing
            simulateVehicleRouting();
            break;
        case 8:
            // manually move a vehicle
            manuallyMoveVehicle();
            break;
        case 9:
            cout << "Exiting Simulation\n";
            break;
        default:
            cout << "Invalid Choice. Please select a valid option.\n";
        }
    }

    return 0;
}
