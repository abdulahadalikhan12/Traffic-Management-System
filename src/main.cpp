#include <iostream>
#include <fstream>
#include <string>
#include "../src/Graph.h"
using namespace std;

// global instance of graph to keep track of all changes
Graph graph;

int main()
{
    int choice = 0;
    graph.createIntersections("../data/traffic_signals.csv");
    graph.createNetwork("../data/road_network.csv");

    /*while(choice != 8)
    {
        cout<< "------ Allah MashAllah Traffic Simulator ------\n";
        cout << "1. Display City Traffic Network\n";
        cout << "2. Display Traffic Signal Status\n";
        cout << "3. Display Congestion Status\n";
        cout << "4. Display Blocked Roads\n";
        cout << "5. Handle Emergency Vehicle Routing\n";
        cout << "6. Block Road Due to Accident\n";
        cout << "7. Simulate Vehicle Routing\n";
        cout << "8. Exit Simulation\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                graph.visualizeNetwork();
                break;
            case 2:
                graph.visualizeSignals();
                break;
            case 3:
                //graph.displayCongestion();
                break;
            case 4:
                //graph.displayBlockedRoads();
                break;
            case 5:
                //graph.handleEmergencyVehicle();
                break;
            case 6:
                //graph.blockRoad();
                break;
            case 7:
                //graph.simulateVehicleRouting();
                break;
            case 8:
                cout << "Exiting Simulation\n";
                break;
            default:
                cout << "Invalid Choice\n";
        }

    }*/

    graph.visualizeNetwork();
    graph.visualizeSignals();

    graph.simulateRoadClosure("../data/road_closures.csv");

    graph.dijkstra('A', 'E');

    return 0;
}