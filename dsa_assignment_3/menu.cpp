#include <iostream>
#include "menu.h"
#include "intake.h"
#include "priority.h"
#include "capacity.h"
#include "search.h"
#include "fileio.h"
using namespace std;

// Member 5: Menu System and Integration (白开水)
// This file connects all modules together through a menu system.

void showPackageMenu() {
    int choice = 0;

    do {
        cout << "\n--- Package Management ---" << endl;
        cout << "1. Add Package" << endl;
        cout << "2. Remove Package" << endl;
        cout << "3. Update Package Status" << endl;
        cout << "4. Display All Packages" << endl;
        cout << "5. Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        while (cin.fail()) {
            cout << "Invalid input. Please enter a number: ";
            clearBuffer();
            cin >> choice;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                addPackage();
                break;
            case 2:
                removePackage();
                break;
            case 3:
                updatePackageStatus();
                break;
            case 4:
                displayAllPackages();
                break;
            case 5:
                cout << "Going back..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 5);
}

void showTruckMenu() {
    int choice = 0;

    do {
        cout << "\n--- Truck Management ---" << endl;
        cout << "1. Add Truck" << endl;
        cout << "2. Display All Trucks" << endl;
        cout << "3. Load Package onto Truck" << endl;
        cout << "4. Dispatch Truck" << endl;
        cout << "5. Return Truck" << endl;
        cout << "6. Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        while (cin.fail()) {
            cout << "Invalid input. Please enter a number: ";
            clearBuffer();
            cin >> choice;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                addTruck();
                break;
            case 2:
                displayAllTrucks();
                break;
            case 3:
                loadPackageToTruck();
                break;
            case 4:
                dispatchTruck();
                break;
            case 5:
                returnTruck();
                break;
            case 6:
                cout << "Going back..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 6);
}

void showPriorityMenu() {
    int choice = 0;

    do {
        cout << "\n--- Priority Queue ---" << endl;
        cout << "1. View Queue (Express First)" << endl;
        cout << "2. Process Next Package" << endl;
        cout << "3. Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        while (cin.fail()) {
            cout << "Invalid input. Please enter a number: ";
            clearBuffer();
            cin >> choice;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                viewPriorityQueue();
                break;
            case 2:
                processNextPackage();
                break;
            case 3:
                cout << "Going back..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 3);
}

void showSearchMenu() {
    int choice = 0;

    do {
        cout << "\n--- Search and Reports ---" << endl;
        cout << "1. Search by Tracking ID" << endl;
        cout << "2. Search by Destination" << endl;
        cout << "3. Search by Sender Name" << endl;
        cout << "4. View Delivered Packages" << endl;
        cout << "5. Generate Summary Report" << endl;
        cout << "6. Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        while (cin.fail()) {
            cout << "Invalid input. Please enter a number: ";
            clearBuffer();
            cin >> choice;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                searchByTrackingID();
                break;
            case 2:
                searchByDestination();
                break;
            case 3:
                searchBySender();
                break;
            case 4:
                displayDeliveredPackages();
                break;
            case 5:
                generateSummaryReport();
                break;
            case 6:
                cout << "Going back..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 6);
}

void runSystem() {
    loadFromFile();

    int choice = 0;

    do {
        cout << "\n==============================" << endl;
        cout << "  LOGISTICS HUB MANAGEMENT   " << endl;
        cout << "==============================" << endl;
        cout << "1. Package Management" << endl;
        cout << "2. Truck Management" << endl;
        cout << "3. Priority Queue" << endl;
        cout << "4. Search and Reports" << endl;
        cout << "5. Save and Exit" << endl;
        cout << "==============================" << endl;
        cout << "Choice: ";
        cin >> choice;
        while (cin.fail()) {
            cout << "Invalid input. Please enter a number: ";
            clearBuffer();
            cin >> choice;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                showPackageMenu();
                break;
            case 2:
                showTruckMenu();
                break;
            case 3:
                showPriorityMenu();
                break;
            case 4:
                showSearchMenu();
                break;
            case 5:
                saveToFile();
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter 1 to 5." << endl;
                break;
        }
    } while (choice != 5);
}
