#include "package.h"
#include "menu.h"

Package packages[MAX_PACKAGES];
int packageCount = 0;

Truck trucks[MAX_TRUCKS];
int truckCount = 0;

void clearBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int findPackage(string trackingID) {
    for (int i = 0; i < packageCount; i++) {
        if (packages[i].trackingID == trackingID) {
            return i;
        }
    }
    return -1;
}

int findTruck(string truckID) {
    for (int i = 0; i < truckCount; i++) {
        if (trucks[i].truckID == truckID) {
            return i;
        }
    }
    return -1;
}

int main() {
    runSystem();
    return 0;
}
