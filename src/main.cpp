#include <iostream>
#include <fstream>
#include <string>
#include "../src/Graph.h"
using namespace std;

Graph graph;

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
        cin >> input1 >> input2;
    }
}

void inputHandlingVehicleMovement(string &vehicleName, char &newIntersection)
{
    cout << "Enter vehicle name (e.g., V1): ";
    cin >> vehicleName;
    cout << "Enter new intersection (A-Z): ";
    cin >> newIntersection;
}

int main()
{
    int choice = 0;

    // Load initial data from CSV files
    graph.createIntersections("data/traffic_signals.csv");
    graph.createNetwork("data/road_network.csv");
    graph.createVehicles("data/vehicles.csv");
    graph.simulateRoadClosure("data/road_closures.csv");

    //test findAllRoutes
    graph.findAllRoutes('W', 'Z');

    //test dijkstra's
    cout<< graph.dijkstra('W', 'Z',0)<<endl;
    cout<< graph.dijkstra('W', 'Z', 1)<<endl;

    //string vehicleName;   // Declare the variable here to use across the switch cases
    //char newIntersection; // Declare the variable here for vehicle movement

    // Start simulation loop
    /*
    while (choice != 9)
    {
        mainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Display the network
            graph.visualizeNetwork();
            break;
        case 2:
            // Display traffic signal status
            graph.visualizeSignals();
            break;
        case 3:
            // Display congestion status
            // graph.displayCongestion();  // Implement if necessary
            break;
        case 4:
            // Display blocked roads
            graph.printBlockedRoads();
            break;
        case 5:
            // Handle emergency vehicle routing
            cout << "Handling emergency vehicle routing...\n";
            // graph.handleEmergencyVehicle();
            break;
        case 6:
            // Block a road due to an accident
            char start, end;
            cout << "Enter road to block (start, end): ";
            cin >> start >> end;
            inputHandlingBlockRoad(start, end);

            graph.blockRoad(start, end);         // Block the road
            graph.rerouteForBlocked(start, end); // Reroute vehicles
            break;
        case 7:
            // Simulate vehicle routing
            // graph.simulateVehicleRouting();  // Implement if necessary
            break;
        case 8:
            // Manually move a vehicle
            inputHandlingVehicleMovement(vehicleName, newIntersection); // Call to get vehicle name and destination
            // graph.moveVehicleToNewIntersection(vehicleName, newIntersection); // Implement this function
            break;
        case 9:
            cout << "Exiting Simulation\n";
            break;
        default:
            cout << "Invalid Choice\n";
        }
    }
    */
    return 0;
}
