#include <iostream>
#include "capacity.h"
using namespace std;

// Member 3: Resource and Capacity Handling

void addTruck() {
    if (truckCount >= MAX_TRUCKS) {
        cout << "Maximum number of trucks reached." << endl;
        return;
    }

    Truck t;
    t.currentLoad = 0;
    t.departed = false;

    cout << "Enter Truck ID: ";
    getline(cin, t.truckID);

    // Check for duplicate truck ID
    if (findTruck(t.truckID) != -1) {
        cout << "Error: Truck ID already exists." << endl;
        return;
    }

    cout << "Enter Destination: ";
    getline(cin, t.destination);

    cout << "Enter Max Capacity (kg): ";
    cin >> t.maxCapacity;
    while (cin.fail() || t.maxCapacity <= 0) {
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid capacity number: ";
        } else {
            cout << "Error: Capacity must be greater than 0. Re-enter: ";
        }
        clearBuffer();
        cin >> t.maxCapacity;
    }
    clearBuffer();

    trucks[truckCount] = t;
    truckCount++;

    cout << "Truck added successfully!" << endl;
}

void displayAllTrucks() {
    if (truckCount == 0) {
        cout << "No trucks in the system." << endl;
        return;
    }

    cout << "\n--- All Trucks (" << truckCount << " total) ---" << endl;

    for (int i = 0; i < truckCount; i++) {
        double remaining = trucks[i].maxCapacity - trucks[i].currentLoad;
        string status;
        if (trucks[i].departed) status = "Departed";
        else status = "Available";

        cout << "[" << i + 1 << "] "
             << "ID: " << trucks[i].truckID
             << " | Dest: " << trucks[i].destination
             << " | Max: " << trucks[i].maxCapacity << "kg"
             << " | Load: " << trucks[i].currentLoad << "kg"
             << " | Remaining: " << remaining << "kg"
             << " | " << status << endl;
    }
}

void loadPackageToTruck() {
    if (packageCount == 0) {
        cout << "No packages in the system." << endl;
        return;
    }
    if (truckCount == 0) {
        cout << "No trucks in the system." << endl;
        return;
    }

    string pkgID;
    cout << "Enter Package Tracking ID: ";
    getline(cin, pkgID);

    // Find the package
    int pIdx = findPackage(pkgID);

    if (pIdx == -1) {
        cout << "Package not found." << endl;
        return;
    }

    if (packages[pIdx].status != "Pending") {
        cout << "Package status is not Pending. Cannot load." << endl;
        return;
    }

    string truckID;
    cout << "Enter Truck ID: ";
    getline(cin, truckID);

    // Find the truck
    int tIdx = findTruck(truckID);

    if (tIdx == -1) {
        cout << "Truck not found." << endl;
        return;
    }

    if (trucks[tIdx].departed) {
        cout << "Truck has already departed." << endl;
        return;
    }

    // Check destination match
    if (packages[pIdx].destination != trucks[tIdx].destination) {
        cout << "Error: Package destination (" << packages[pIdx].destination 
             << ") does not match truck destination (" << trucks[tIdx].destination << ")." << endl;
        return;
    }

    double remaining = trucks[tIdx].maxCapacity - trucks[tIdx].currentLoad;

    if (packages[pIdx].weight > remaining) {
        cout << "Not enough space on the truck." << endl;
        cout << "Package weight: " << packages[pIdx].weight << " kg" << endl;
        cout << "Remaining space: " << remaining << " kg" << endl;
        return;
    }

    trucks[tIdx].currentLoad += packages[pIdx].weight;
    packages[pIdx].status = "Loaded";
    packages[pIdx].truckIndex = tIdx;

    cout << "Package loaded onto truck successfully!" << endl;
    cout << "Remaining truck capacity: " << (trucks[tIdx].maxCapacity - trucks[tIdx].currentLoad) << " kg" << endl;
}

void dispatchTruck() {
    if (truckCount == 0) {
        cout << "No trucks in the system." << endl;
        return;
    }

    string truckID;
    cout << "Enter Truck ID to dispatch: ";
    getline(cin, truckID);

    int tIdx = findTruck(truckID);

    if (tIdx == -1) {
        cout << "Truck not found." << endl;
        return;
    }

    if (trucks[tIdx].departed) {
        cout << "Truck has already departed." << endl;
        return;
    }

    trucks[tIdx].departed = true;

    // Mark all packages on this truck as Delivered
    int deliveredCount = 0;
    for (int i = 0; i < packageCount; i++) {
        if (packages[i].truckIndex == tIdx && packages[i].status == "Loaded") {
            packages[i].status = "Delivered";
            deliveredCount++;
        }
    }

    cout << "Truck " << truckID << " has departed to " << trucks[tIdx].destination << "." << endl;
    cout << deliveredCount << " package(s) marked as Delivered." << endl;
}

void returnTruck() {
    if (truckCount == 0) {
        cout << "No trucks in the system." << endl;
        return;
    }

    string truckID;
    cout << "Enter Truck ID to return: ";
    getline(cin, truckID);

    int tIdx = findTruck(truckID);

    if (tIdx == -1) {
        cout << "Truck not found." << endl;
        return;
    }

    if (!trucks[tIdx].departed) {
        cout << "Truck has not departed yet." << endl;
        return;
    }

    trucks[tIdx].departed = false;
    trucks[tIdx].currentLoad = 0;

    cout << "Truck " << truckID << " has returned and is now available." << endl;
}
