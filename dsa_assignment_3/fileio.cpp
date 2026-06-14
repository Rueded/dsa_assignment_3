#include <iostream>
#include <fstream>
#include "fileio.h"
#include "package.h"
using namespace std;

// Save all data to text files

void saveToFile() {
    ofstream pkgFile("packages.txt");
    if (!pkgFile) {
        cout << "Could not save packages." << endl;
    } else {
        pkgFile << packageCount << endl;
        for (int i = 0; i < packageCount; i++) {
            pkgFile << packages[i].trackingID << endl;
            pkgFile << packages[i].senderName << endl;
            pkgFile << packages[i].receiverName << endl;
            pkgFile << packages[i].destination << endl;
            pkgFile << packages[i].weight << endl;
            pkgFile << packages[i].priority << endl;
            pkgFile << packages[i].status << endl;
            pkgFile << packages[i].truckIndex << endl;
        }
        pkgFile.close();
        cout << "Packages saved to packages.txt" << endl;
    }

    ofstream trkFile("trucks.txt");
    if (!trkFile) {
        cout << "Could not save trucks." << endl;
    } else {
        trkFile << truckCount << endl;
        for (int i = 0; i < truckCount; i++) {
            trkFile << trucks[i].truckID << endl;
            trkFile << trucks[i].destination << endl;
            trkFile << trucks[i].maxCapacity << endl;
            trkFile << trucks[i].currentLoad << endl;
            trkFile << trucks[i].departed << endl;
        }
        trkFile.close();
        cout << "Trucks saved to trucks.txt" << endl;
    }
}

// Load data from text files (called when program starts)

void loadFromFile() {
    ifstream pkgFile("packages.txt");
    if (!pkgFile) {
        return; // No saved file, start fresh
    }

    int tempPkgCount = 0;
    if (!(pkgFile >> tempPkgCount)) {
        pkgFile.close();
        return;
    }
    pkgFile.ignore();

    if (tempPkgCount > MAX_PACKAGES) {
        tempPkgCount = MAX_PACKAGES;
    }

    int loadedPkgs = 0;
    for (int i = 0; i < tempPkgCount; i++) {
        if (!getline(pkgFile, packages[i].trackingID)) break;
        if (!getline(pkgFile, packages[i].senderName)) break;
        if (!getline(pkgFile, packages[i].receiverName)) break;
        if (!getline(pkgFile, packages[i].destination)) break;
        if (!(pkgFile >> packages[i].weight)) break;
        if (!(pkgFile >> packages[i].priority)) break;
        pkgFile.ignore();
        if (!getline(pkgFile, packages[i].status)) break;
        if (!(pkgFile >> packages[i].truckIndex)) break;
        pkgFile.ignore();
        loadedPkgs++;
    }
    packageCount = loadedPkgs;
    pkgFile.close();

    ifstream trkFile("trucks.txt");
    if (!trkFile) {
        return;
    }

    int tempTrkCount = 0;
    if (!(trkFile >> tempTrkCount)) {
        trkFile.close();
        return;
    }
    trkFile.ignore();

    if (tempTrkCount > MAX_TRUCKS) {
        tempTrkCount = MAX_TRUCKS;
    }

    int loadedTrks = 0;
    for (int i = 0; i < tempTrkCount; i++) {
        if (!getline(trkFile, trucks[i].truckID)) break;
        if (!getline(trkFile, trucks[i].destination)) break;
        if (!(trkFile >> trucks[i].maxCapacity)) break;
        if (!(trkFile >> trucks[i].currentLoad)) break;
        if (!(trkFile >> trucks[i].departed)) break;
        trkFile.ignore();
        loadedTrks++;
    }
    truckCount = loadedTrks;
    trkFile.close();

    cout << "Previous data loaded. (" << packageCount << " packages, " << truckCount << " trucks)" << endl;
}
