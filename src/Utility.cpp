// Utility.cpp
#include "Utility.h"
#include <iostream>
#include <limits>
#include "../src/Graph.h"
#include "../src/TrafficMonitor.h"

extern Graph graph;            // extern because it's defined in main file
extern TrafficMonitor monitor;

int getValidChoice()
{
    int choice;
    while (true)
    {
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) // check if the input is invalid
        {
            std::cin.clear();                                                   // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
            std::cout << "Invalid input. Please enter a number between 1 and 9.\n";
        }
        else if (choice >= 1 && choice <= 9)
        {
            break; // valid choice
        }
        else
        {
            std::cout << "Invalid choice. Please enter a number between 1 and 9.\n";
        }
    }
    return choice;
}

void mainMenu()
{
    std::cout << "------ Welcome To Allah MashAllah Traffic Simulator ------\n";
    std::cout << "1. Display City Traffic Network\n";
    std::cout << "2. Display Traffic Signal Status\n";
    std::cout << "3. Display Congestion Status\n";
    std::cout << "4. Display Blocked Roads\n";
    std::cout << "5. Handle Emergency Vehicle Routing\n";
    std::cout << "6. Block Road Due to Accident\n";
    std::cout << "7. Simulate Vehicle Routing\n";
    std::cout << "8. Manually Move Vehicle\n";
    std::cout << "9. Exit Simulation\n\n";
}

bool isValidIntersection(char intersection)
{
    return intersection >= 'A' && intersection <= 'Z';
}

bool isValidVehicleName(const std::string &vehicleName)
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

void inputHandlingVehicleMovement(std::string &vehicleName, char &newIntersection)
{
    do
    {
        std::cout << "Enter vehicle name (e.g., V1): ";
        std::cin >> vehicleName;
        if (!isValidVehicleName(vehicleName))
            std::cout << "Invalid vehicle name. Please use the format 'V<number>' (e.g., V1).\n";
    } while (!isValidVehicleName(vehicleName));

    do
    {
        std::cout << "Enter new intersection (A-Z): ";
        std::cin >> newIntersection;
    } while (!isValidIntersection(newIntersection));
}

void inputHandlingBlockRoad(char &input1, char &input2)
{
    while (!isValidIntersection(input1) || !isValidIntersection(input2))
    {
        std::cout << "Invalid input. Please enter valid road intersections (A-Z): ";
        std::cout << "Enter First Intersection: ";
        std::cin >> input1;
        std::cout << "Enter Second Intersection: ";
        std::cin >> input2;
    }
}

void loadData()
{
    if (!graph.createIntersections("data/traffic_signals.csv"))
    {
        std::cerr << "Error: Failed to load traffic signals data.\n";
        exit(1);
    }
    if (!graph.createNetwork("data/road_network.csv"))
    {
        std::cerr << "Error: Failed to load road network data.\n";
        exit(1);
    }
    if (!graph.createVehicles("data/vehicles.csv"))
    {
        std::cerr << "Error: Failed to load vehicles data.\n";
        exit(1);
    }
    if (!graph.simulateRoadClosure("data/road_closures.csv"))
    {
        std::cerr << "Error: Failed to load road closures data.\n";
        exit(1);
    }
}

void handleBlockedRoad()
{
    char start, end;
    std::cout << "Enter road to block (start, end): ";
    std::cin >> start >> end;
    inputHandlingBlockRoad(start, end);

    std::cout << "Blocking road " << start << " -> " << end << std::endl;
    graph.blockRoad(start, end);         // block the road
    graph.rerouteForBlocked(start, end); // reroute vehicles
}

void simulateVehicleRouting()
{
    char starting, ending;

    // input validation for starting intersection
    do
    {
        std::cout << "Enter Starting Intersection (A-Z): ";
        std::cin >> starting;
    } while (!isValidIntersection(starting)); // check if the input is valid

    // input validation for ending intersection
    do
    {
        std::cout << "Enter Ending Intersection (A-Z): ";
        std::cin >> ending;
    } while (!isValidIntersection(ending)); // check if the input is valid

    std::cout << "Simulating route from " << starting << " to " << ending << std::endl;
    graph.findAllRoutes(starting, ending);
}

void manuallyMoveVehicle()
{
    std::string vehicleName;
    char newIntersection;
    inputHandlingVehicleMovement(vehicleName, newIntersection);
    std::cout << "Moving vehicle " << vehicleName << " to intersection " << newIntersection << std::endl;
    graph.moveVehicleToNewIntersection(vehicleName, newIntersection);
}
