#include <iostream>
#include <fstream>
#include <string>
#include "../src/Graph.h"
#include "../src/TrafficMonitor.h"
using namespace std;

Graph graph;
TrafficMonitor monitor;

void mainMenu()
{
    cout << "------ Welcome To Allah MashAllah Traffic Simulator ------\n";
    cout << "1. Display City Traffic Network\n";
    cout << "2. Display Traffic Signal Status\n";
    cout << "3. Display Congestion Status\n";
    cout << "4. Display Blocked Roads\n";
    cout << "5. Handle Emergency Vehicle Routing\n";
    cout << "6. Block Road Due to Accident\n";
    cout << "7. Simulate Vehicle Routing\n";
    cout << "8. Manually Move Vehicle\n";
    cout << "9. Exit Simulation\n\n";
}

void inputHandlingBlockRoad(char &input1, char &input2)
{
    while ((input1 < 'A' || input1 > 'Z') || (input2 < 'A' || input2 > 'Z'))
    {
        cout << "Invalid input. Please enter valid road intersections (A-Z): ";
        cout << "Enter First Intersection: ";
        cin >> input1;
        cout << "Enter Second Intersection: ";
        cin >> input2;
    }
}

void inputHandlingVehicleMovement(string &vehicleName, char &newIntersection)
{
    cout << "Enter vehicle name (e.g., V1): ";
    cin >> vehicleName;

    do
    {
        cout << "Enter new intersection (A-Z): ";
        cin >> newIntersection;
    } while (newIntersection < 'A' || newIntersection > 'Z');
}

int main()
{
    int choice = 0;

    // Load initial data from CSV files
    graph.createIntersections("data/traffic_signals.csv");
    graph.createNetwork("data/road_network.csv");
    graph.createVehicles("data/vehicles.csv");
    graph.simulateRoadClosure("data/road_closures.csv");

    // test findAllRoutes
    // graph.findAllRoutes('A', 'D');


    string vehicleName;   // Declare the variable here to use across the switch cases
    char newIntersection; // Declare the variable here for vehicle movement

    // Start simulation loop
    while (choice != 9)
    {
        mainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Display the network
            cout << "Displaying City Traffic Network...\n";
            graph.visualizeNetwork();
            break;
        case 2:
            // Display traffic signal status
            cout << "Displaying Traffic Signal Status...\n";
            graph.visualizeSignals();
            break;
        case 3:
            // Display congestion status
            cout << "Displaying Congestion Status...\n";
            monitor.displayTrafficStatus();
            break;
        case 4:
            // Display blocked roads
            cout << "Displaying Blocked Roads...\n";
            graph.printBlockedRoads();
            break;
        case 5:
            // Handle emergency vehicle routing
            cout << "Handling emergency vehicle routing...\n";
            // graph.handleEmergencyVehicle(); // Uncomment once implemented
            break;
        case 6:
            // Block a road due to an accident
            char start, end;
            cout << "Enter road to block (start, end): ";
            cin >> start >> end;
            inputHandlingBlockRoad(start, end);

            cout << "Blocking road " << start << " -> " << end << endl;
            graph.blockRoad(start, end);         // Block the road
            graph.rerouteForBlocked(start, end); // Reroute vehicles
            break;
        case 7:
            // Simulate vehicle routing
            char starting, ending;
            cout << "Enter Starting Intersection (A-Z): ";
            cin >> starting;
            cout << "Enter Ending Intersection (A-Z): ";
            cin >> ending;
            inputHandlingBlockRoad(starting, ending);

            cout << "Simulating route from " << starting << " to " << ending << endl;
            graph.findAllRoutes(starting, ending);
            break;
        case 8:
            // manually move a vehicle
            inputHandlingVehicleMovement(vehicleName, newIntersection);
            cout << "Moving vehicle " << vehicleName << " to intersection " << newIntersection << endl;
            graph.moveVehicleToNewIntersection(vehicleName, newIntersection);
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