#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <iostream>
using namespace std;

void clearBuffer();

const int MAX_PACKAGES = 100;
const int MAX_TRUCKS = 10;

struct Package {
    string trackingID;
    string senderName;
    string receiverName;
    string destination;
    double weight;
    int priority;    // 1 = Express, 2 = Standard
    string status;   // "Pending", "Loaded", "Delivered", "Cancelled"
    int truckIndex;  // -1 if not assigned to any truck

    string getPriorityStr() { return (priority == 1) ? "Express" : "Standard"; }
};

struct Truck {
    string truckID;
    string destination;
    double maxCapacity;
    double currentLoad;
    bool departed;
};

extern Package packages[MAX_PACKAGES];
extern int packageCount;

extern Truck trucks[MAX_TRUCKS];
extern int truckCount;

int findPackage(string trackingID);
int findTruck(string truckID);

#endif
