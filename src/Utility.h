// Utility.h
#ifndef UTILITY_H
#define UTILITY_H

#include <string>

int getValidChoice();
void mainMenu();
bool isValidIntersection(char intersection);
bool isValidVehicleName(const std::string &vehicleName);
void inputHandlingVehicleMovement(std::string &vehicleName, char &newIntersection);
void inputHandlingBlockRoad(char &input1, char &input2);
void loadData();
void handleBlockedRoad();
void simulateVehicleRouting();
void manuallyMoveVehicle();

#endif // UTILITY_H
