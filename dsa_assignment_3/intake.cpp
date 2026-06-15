#include <iostream>
#include <iomanip>
#include "intake.h"
using namespace std;

// Member 1: Data Intake and Validation

void addPackage() {
    if (packageCount >= MAX_PACKAGES) {
        cout << "Package storage is full!" << endl;
        return;
    }

    Package p;
    p.truckIndex = -1;
    p.status = "Pending";

    cout << "Enter Tracking ID: ";
    getline(cin, p.trackingID);

    // Check for duplicate tracking ID
    if (findPackage(p.trackingID) != -1) {
        cout << "Error: Tracking ID already exists." << endl;
        return;
    }

    cout << "Enter Sender Name: ";
    getline(cin, p.senderName);

    cout << "Enter Receiver Name: ";
    getline(cin, p.receiverName);

    cout << "Enter Destination: ";
    getline(cin, p.destination);

    cout << "Enter Weight (kg): ";
    cin >> p.weight;
    while (cin.fail() || p.weight <= 0) {
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid number for weight: ";
        } else {
            cout << "Error: Weight must be greater than 0. Re-enter: ";
        }
        clearBuffer();
        cin >> p.weight;
    }
    //clearBuffer();

    cout << "Enter Priority (1 = Express, 2 = Standard): ";
    cin >> p.priority;
    while (cin.fail() || (p.priority != 1 && p.priority != 2)) {
        if (cin.fail()) {
            cout << "\nInvalid input. Enter Priority (1 = Express, 2 = Standard): ";
        } else {
            cout << "\nInvalid priority. Enter Priority (1 = Express, 2 = Standard): ";
        }
        clearBuffer();
        cin >> p.priority;
    }
    clearBuffer();

    packages[packageCount] = p;
    packageCount++;

    cout << "Package added successfully!" << endl;
}

void removePackage() {
    if (packageCount == 0) {
        cout << "No packages in the system." << endl;
        return;
    }

    string id;
    cout << "Enter Tracking ID to remove: ";
    getline(cin, id);

    int index = findPackage(id);

    if (index == -1) {
        cout << "Package not found." << endl;
        return;
    }

    if (packages[index].status != "Pending") {
    cout << "Can only remove Pending packages." << endl;
    return;
}

    // Shift array left to fill the gap
    for (int i = index; i < packageCount - 1; i++) {
        packages[i] = packages[i + 1];
    }
    packageCount--;

    cout << "Package removed successfully." << endl;
}

void updatePackageStatus() {
    if (packageCount == 0) {
        cout << "No packages in the system." << endl;
        return;
    }

    string id;
    cout << "Enter Tracking ID: ";
    getline(cin, id);

    int index = findPackage(id);

    if (index == -1) {
        cout << "Package not found." << endl;
        return;
    }

    bool oldStatusLoaded = (packages[index].status == "Loaded");
    int oldTruckIdx = packages[index].truckIndex;

    cout << "Current Status: " << packages[index].status << endl;
    cout << "Select new status:" << endl;
    cout << "1. Pending" << endl;
    cout << "2. Loaded" << endl;
    cout << "3. Delivered" << endl;
    cout << "4. Cancelled" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 4) {
        cout << "Invalid choice. Please enter a number between 1 and 4: ";
        clearBuffer();
        cin >> choice;
    }
    clearBuffer();

    string newStatus = "";
    if (choice == 1) newStatus = "Pending";
    else if (choice == 2) newStatus = "Loaded";
    else if (choice == 3) newStatus = "Delivered";
    else if (choice == 4) newStatus = "Cancelled";

    if (newStatus == packages[index].status) {
        cout << "Status is already " << newStatus << "." << endl;
        return;
    }

    if (newStatus == "Loaded") {
        if (truckCount == 0) {
            cout << "No trucks in the system. Cannot mark as Loaded." << endl;
            return;
        }
        string truckID;
        cout << "Enter Truck ID to load onto: ";
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
        if (packages[index].destination != trucks[tIdx].destination) {
            cout << "Error: Package destination (" << packages[index].destination 
                 << ") does not match truck destination (" << trucks[tIdx].destination << ")." << endl;
            return;
        }
        double remaining = trucks[tIdx].maxCapacity - trucks[tIdx].currentLoad;
        if (packages[index].weight > remaining) {
            cout << "Not enough space on the truck." << endl;
            return;
        }

        // If it was already loaded on a different truck, remove it from that truck first
        if (oldStatusLoaded && oldTruckIdx >= 0 && oldTruckIdx < truckCount) {
            trucks[oldTruckIdx].currentLoad -= packages[index].weight;
            if (trucks[oldTruckIdx].currentLoad < 0) {
                trucks[oldTruckIdx].currentLoad = 0;
            }
        }

        trucks[tIdx].currentLoad += packages[index].weight;
        packages[index].status = "Loaded";
        packages[index].truckIndex = tIdx;
        cout << "Status updated to Loaded. Package loaded onto truck " << truckID << "." << endl;
    } else {
        // If transitioning away from Loaded, release the old truck capacity
        if (oldStatusLoaded && oldTruckIdx >= 0 && oldTruckIdx < truckCount) {
            trucks[oldTruckIdx].currentLoad -= packages[index].weight;
            if (trucks[oldTruckIdx].currentLoad < 0) {
                trucks[oldTruckIdx].currentLoad = 0;
            }
        }
        packages[index].status = newStatus;
        packages[index].truckIndex = -1;
        cout << "Status updated to " << newStatus << "." << endl;
    }
}

void displayAllPackages() {
    if (packageCount == 0) {
        cout << "No packages in the system." << endl;
        return;
    }

    cout << "\n--- All Packages (" << packageCount << " total) ---" << endl;

    for (int i = 0; i < packageCount; i++) {
        cout << "[" << setw(2) << right << (i + 1) << "] "
             << "ID: " << left << setw(12) << packages[i].trackingID
             << " | Sender: " << setw(15) << packages[i].senderName
             << " | Receiver: " << setw(15) << packages[i].receiverName
             << " | Dest: " << setw(15) << packages[i].destination
             << " | " << right << fixed << setprecision(1) << setw(6) << packages[i].weight << " kg"
             << " | " << left << setw(10) << packages[i].getPriorityStr()
             << " | " << setw(10) << packages[i].status << endl;
    }
}
