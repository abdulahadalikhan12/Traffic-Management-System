#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "../src/Graph.h"
#include "../src/TrafficMonitor.h"
using namespace std;

Graph graph;
TrafficMonitor monitor;

int getValidChoice()
{
    int choice;
    while (true)
    {
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) // check if the input is invalid
        {
            cin.clear();                                         // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
        }
        else if (choice >= 1 && choice <= 9)
        {
            break; // valid choice
        }
        else
        {
            cout << "Invalid choice. Please enter a number between 1 and 9.\n";
        }
    }
    return choice;
}

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

bool isValidIntersection(char intersection)
{
    return intersection >= 'A' && intersection <= 'Z';
}

bool isValidVehicleName(const string &vehicleName)
{
    if (vehicleName.length() < 2 || vehicleName[0] != 'V')
        return false;
    for (size_t i = 1; i < vehicleName.length(); ++i)
    {
        if (!isdigit(vehicleName[i]))
            return false;
    }
    return true;
}

void inputHandlingVehicleMovement(string &vehicleName, char &newIntersection)
{
    do
    {
        cout << "Enter vehicle name (e.g., V1): ";
        cin >> vehicleName;
        if (!isValidVehicleName(vehicleName))
            cout << "Invalid vehicle name. Please use the format 'V<number>' (e.g., V1).\n";
    } while (!isValidVehicleName(vehicleName));

    do
    {
        cout << "Enter new intersection (A-Z): ";
        cin >> newIntersection;
    } while (!isValidIntersection(newIntersection));
}

void inputHandlingBlockRoad(char &input1, char &input2)
{
    while (!isValidIntersection(input1) || !isValidIntersection(input2))
    {
        cout << "Invalid input. Please enter valid road intersections (A-Z): ";
        cout << "Enter First Intersection: ";
        cin >> input1;
        cout << "Enter Second Intersection: ";
        cin >> input2;
    }
}

void loadData()
{
    if (!graph.createIntersections("data/traffic_signals.csv"))
    {
        cerr << "Error: Failed to load traffic signals data.\n";
        exit(1);
    }
    if (!graph.createNetwork("data/road_network.csv"))
    {
        cerr << "Error: Failed to load road network data.\n";
        exit(1);
    }
    if (!graph.createVehicles("data/vehicles.csv"))
    {
        cerr << "Error: Failed to load vehicles data.\n";
        exit(1);
    }
    if (!graph.simulateRoadClosure("data/road_closures.csv"))
    {
        cerr << "Error: Failed to load road closures data.\n";
        exit(1);
    }
}

void handleBlockedRoad()
{
    char start, end;
    cout << "Enter road to block (start, end): ";
    cin >> start >> end;
    inputHandlingBlockRoad(start, end);

    cout << "Blocking road " << start << " -> " << end << endl;
    graph.blockRoad(start, end);         // Block the road
    graph.rerouteForBlocked(start, end); // Reroute vehicles
}

void simulateVehicleRouting()
{
    char starting, ending;

    // Input validation for starting intersection
    do
    {
        cout << "Enter Starting Intersection (A-Z): ";
        cin >> starting;
    } while (!isValidIntersection(starting)); // Check if the input is valid

    // Input validation for ending intersection
    do
    {
        cout << "Enter Ending Intersection (A-Z): ";
        cin >> ending;
    } while (!isValidIntersection(ending)); // Check if the input is valid

    cout << "Simulating route from " << starting << " to " << ending << endl;
    graph.findAllRoutes(starting, ending);
}

void manuallyMoveVehicle()
{
    string vehicleName;
    char newIntersection;
    inputHandlingVehicleMovement(vehicleName, newIntersection);
    cout << "Moving vehicle " << vehicleName << " to intersection " << newIntersection << endl;
    graph.moveVehicleToNewIntersection(vehicleName, newIntersection);
}

int main()
{
    int choice = 0;

    // Load initial data from CSV files
    loadData();

    // Start simulation loop
    while (choice != 9)
    {
        mainMenu();
        choice = getValidChoice();

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
            handleBlockedRoad();
            break;
        case 7:
            // Simulate vehicle routing
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
