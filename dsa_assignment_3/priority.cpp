#include <iostream>
#include <iomanip>
#include "priority.h"
using namespace std;

// Member 2: Ordering and Prioritisation
// Express (priority 1) comes before Standard (priority 2)
// We collect pending package indexes, then sort by priority using bubble sort

void viewPriorityQueue() {
    // Collect indexes of all pending packages
    int idx[MAX_PACKAGES];
    int count = 0;

    for (int i = 0; i < packageCount; i++) {
        if (packages[i].status == "Pending") {
            idx[count] = i;
            count++;
        }
    }

    if (count == 0) {
        cout << "No pending packages." << endl;
        return;
    }

    // Bubble sort: put Express (1) before Standard (2)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (packages[idx[j]].priority > packages[idx[j + 1]].priority) {
                int temp = idx[j];
                idx[j] = idx[j + 1];
                idx[j + 1] = temp;
            }
        }
    }

    cout << "\n--- Processing Queue (Express First) ---" << endl;

    for (int i = 0; i < count; i++) {
        int k = idx[i];

        cout << setw(2) << right << (i + 1) << ". "
             << left << setw(12) << packages[k].trackingID
             << " | Dest: " << setw(15) << packages[k].destination
             << " | " << right << fixed << setprecision(1) << setw(6) << packages[k].weight << " kg"
             << " | " << left << setw(10) << packages[k].getPriorityStr() << endl;
    }

    cout << "Total pending: " << count << endl;
}

void processNextPackage() {
    // Find next package to process (Express first, then Standard)
    int bestIndex = -1;

    for (int i = 0; i < packageCount; i++) {
        if (packages[i].status == "Pending") {
            if (bestIndex == -1) {
                bestIndex = i;
            } else if (packages[i].priority < packages[bestIndex].priority) {
                bestIndex = i;
            }
        }
    }

    if (bestIndex == -1) {
        cout << "No pending packages to process." << endl;
        return;
    }

    cout << "\n--- Next Package to Process ---" << endl;
    cout << "Tracking ID : " << packages[bestIndex].trackingID << endl;
    cout << "Destination : " << packages[bestIndex].destination << endl;
    cout << "Weight      : " << packages[bestIndex].weight << " kg" << endl;
    cout << "Priority    : " << packages[bestIndex].getPriorityStr() << endl;

    cout << "Mark as Loaded? (1 = Yes, 0 = No): ";
    int confirm;
    cin >> confirm;
    while (cin.fail() || (confirm != 0 && confirm != 1)) {
        cout << "Invalid choice. Enter 1 for Yes, 0 for No: ";
        clearBuffer();
        cin >> confirm;
    }
    clearBuffer();

    if (confirm == 1) {
        if (truckCount == 0) {
            cout << "No trucks in the system. Cannot load." << endl;
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
        if (packages[bestIndex].destination != trucks[tIdx].destination) {
            cout << "Error: Package destination (" << packages[bestIndex].destination 
                 << ") does not match truck destination (" << trucks[tIdx].destination << ")." << endl;
            return;
        }
        double remaining = trucks[tIdx].maxCapacity - trucks[tIdx].currentLoad;
        if (packages[bestIndex].weight > remaining) {
            cout << "Not enough space on the truck." << endl;
            return;
        }

        trucks[tIdx].currentLoad += packages[bestIndex].weight;
        packages[bestIndex].status = "Loaded";
        packages[bestIndex].truckIndex = tIdx;
        cout << "Package marked as Loaded onto truck " << truckID << "." << endl;
    } else {
        cout << "Cancelled." << endl;
    }
}
