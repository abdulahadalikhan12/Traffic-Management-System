#include <iostream>
#include <fstream>
#include <string>
#include "../src/Graph.h"
using namespace std;

// global instance of graph to keep track of all changes
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
    cout << "8. Exit Simulation\n\n";
}

void inputHandlingBlockRoad(char &input1, char &input2){
    
    while((input1 < 'A' || input1 > 'Z') || (input2 < 'A' || input2 > 'Z')){
        cout<<"Either one or both were Ivalid Inputs. Please enter a Capital Letter(A-Z): ";
        cin>>input1 >> input2;
    }

}


int main()
{
    int choice = 0;

    graph.createIntersections("data/traffic_signals.csv");
    graph.createNetwork("data/road_network.csv");
    graph.createVehicles("data/vehicles.csv");
    graph.simulateRoadClosure("data/road_closures.csv");
    graph.rerouteNetwork();

    while(choice != 8){
        mainMenu();
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
                graph.printBlockedRoads();
                break;
            case 5:
                //graph.handleEmergencyVehicle();
                break;
            case 6:
                cout<<"Enter road to block(start, end): ";
                char start, end;
                cin >> start >> end;

                inputHandlingBlockRoad(start, end);
    
                graph.blockRoad(start, end);
                graph.rerouteForBlocked(start, end);
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
    }
    // graph.createIntersections("data/traffic_signals.csv");
    // graph.createNetwork("data/road_network.csv");
    // graph.createVehicles("data/vehicles.csv");
    // graph.simulateRoadClosure("data/road_closures.csv");

    // //Updating Status of Roads

    // // test efficient move
    // graph.visualizeNetwork();
    // graph.printBlockedRoads();
    // graph.moveVehiclesEfficiently("V1");

    // cout<<"\nAfter re-routing:\n";
    // graph.rerouteNetwork();
    
    return 0;
}



/*

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