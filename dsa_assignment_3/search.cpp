#include <iostream>
#include "search.h"
using namespace std;

// Member 4: Search and Reporting (白开水)

// Helper: print one package's full details
void printPackageInfo(int i) {
    string assignedTruck = "None";
    if (packages[i].truckIndex >= 0 && packages[i].truckIndex < truckCount) {
        assignedTruck = trucks[packages[i].truckIndex].truckID;
    }

    cout << "  Tracking ID   : " << packages[i].trackingID << endl;
    cout << "  Sender        : " << packages[i].senderName << endl;
    cout << "  Receiver      : " << packages[i].receiverName << endl;
    cout << "  Destination   : " << packages[i].destination << endl;
    cout << "  Weight        : " << packages[i].weight << " kg" << endl;
    cout << "  Priority      : " << packages[i].getPriorityStr() << endl;
    cout << "  Status        : " << packages[i].status << endl;
    cout << "  Assigned Truck: " << assignedTruck << endl;
}

// Search by exact tracking ID
void searchByTrackingID() {
    if (packageCount == 0) {
        cout << "No packages in the system." << endl;
        return;
    }

    string id;
    cout << "Enter Tracking ID: ";
    getline(cin, id);

    int index = findPackage(id);
    if (index != -1) {
        cout << "\n--- Package Found ---" << endl;
        printPackageInfo(index);
        return;
    }

    cout << "No package found with that Tracking ID." << endl;
}

// Search by destination (exact match)
void searchByDestination() {
    if (packageCount == 0) {
        cout << "No packages in the system." << endl;
        return;
    }

    string dest;
    cout << "Enter Destination: ";
    getline(cin, dest);

    int found = 0;
    cout << "\n--- Search Results ---" << endl;

    for (int i = 0; i < packageCount; i++) {
        if (packages[i].destination == dest) {
            printPackageInfo(i);
            cout << "  --------------------------------" << endl;
            found++;
        }
    }

    if (found == 0) {
        cout << "No packages found for destination: " << dest << endl;
    } else {
        cout << "Total found: " << found << endl;
    }
}

// Search by sender name (exact match)
void searchBySender() {
    if (packageCount == 0) {
        cout << "No packages in the system." << endl;
        return;
    }

    string sender;
    cout << "Enter Sender Name: ";
    getline(cin, sender);

    int found = 0;
    cout << "\n--- Search Results ---" << endl;

    for (int i = 0; i < packageCount; i++) {
        if (packages[i].senderName == sender) {
            printPackageInfo(i);
            cout << "  --------------------------------" << endl;
            found++;
        }
    }

    if (found == 0) {
        cout << "No packages found for sender: " << sender << endl;
    } else {
        cout << "Total found: " << found << endl;
    }
}

// Summary report of all packages and trucks
void generateSummaryReport() {
    cout << "\n========================================" << endl;
    cout << "      LOGISTICS HUB SUMMARY REPORT     " << endl;
    cout << "========================================" << endl;

    int pending = 0, loaded = 0, delivered = 0, cancelled = 0;
    int express = 0, standard = 0;
    double totalWeight = 0;

    for (int i = 0; i < packageCount; i++) {
        if (packages[i].status == "Pending")   pending++;
        if (packages[i].status == "Loaded")    loaded++;
        if (packages[i].status == "Delivered") delivered++;
        if (packages[i].status == "Cancelled") cancelled++;
        if (packages[i].priority == 1) express++;
        else standard++;
        totalWeight += packages[i].weight;
    }

    cout << "\n[Packages]" << endl;
    cout << "  Total     : " << packageCount << endl;
    cout << "  Pending   : " << pending << endl;
    cout << "  Loaded    : " << loaded << endl;
    cout << "  Delivered : " << delivered << endl;
    cout << "  Cancelled : " << cancelled << endl;
    cout << "  Express   : " << express << endl;
    cout << "  Standard  : " << standard << endl;
    cout << "  Total Weight: " << totalWeight << " kg" << endl;

    cout << "\n[Trucks]" << endl;
    cout << "  Total     : " << truckCount << endl;

    int departed = 0, available = 0;
    for (int i = 0; i < truckCount; i++) {
        if (trucks[i].departed) departed++;
        else available++;
    }

    cout << "  Available : " << available << endl;
    cout << "  Departed  : " << departed << endl;

    if (truckCount > 0) {
        cout << "\n[Truck Details]" << endl;
        for (int i = 0; i < truckCount; i++) {
            string status;
            if (trucks[i].departed) status = "Departed";
            else status = "Available";

            cout << "  " << trucks[i].truckID
                 << " | Dest: " << trucks[i].destination
                 << " | Load: " << trucks[i].currentLoad << "/" << trucks[i].maxCapacity << " kg"
                 << " | " << status << endl;
        }
    }

    cout << "========================================" << endl;
}

// Show only delivered packages
void displayDeliveredPackages() {
    if (packageCount == 0) {
        cout << "No packages in the system." << endl;
        return;
    }

    cout << "\n--- Delivered Packages ---" << endl;
    int count = 0;

    for (int i = 0; i < packageCount; i++) {
        if (packages[i].status == "Delivered") {
            string truckName = "Unknown";
            if (packages[i].truckIndex >= 0 && packages[i].truckIndex < truckCount) {
                truckName = trucks[packages[i].truckIndex].truckID;
            }

            cout << packages[i].trackingID
                 << " | Receiver: " << packages[i].receiverName
                 << " | Dest: " << packages[i].destination
                 << " | Truck: " << truckName << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "No delivered packages yet." << endl;
    } else {
        cout << "Total delivered: " << count << endl;
    }
}
