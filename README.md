# Logistics Hub Management System
**KT14603 Data Structures and Algorithms — Lab Assignment 3**

A menu-driven C++ console application that simulates a real-world logistics hub, handling package intake, prioritised processing, truck capacity management, and search/reporting.

---

## How to Compile and Run

**Option A — Using Makefile (Linux/Mac)**
```
make
./logistics
```

**Option B — Manual compile (Windows/Linux/Mac)**
```
g++ main.cpp intake.cpp priority.cpp capacity.cpp search.cpp fileio.cpp menu.cpp -o logistics
./logistics
```

**Option C — On Windows (MinGW)**
```
g++ main.cpp intake.cpp priority.cpp capacity.cpp search.cpp fileio.cpp menu.cpp -o logistics.exe
logistics.exe
```

> Data is saved to `packages.txt` and `trucks.txt` when you exit the program (Option 5 on the main menu). These files are loaded automatically on the next run.

---

## File Structure

| File | Description | Member |
|---|---|---|
| `package.h` | Shared structs (Package, Truck) and global array declarations | All |
| `main.cpp` | Program entry point; defines global arrays | All |
| `intake.h / .cpp` | Add, remove, update, display packages | Member 1 |
| `priority.h / .cpp` | Priority queue (Express first), bubble sort | Member 2 |
| `capacity.h / .cpp` | Truck management, capacity limit, dispatch | Member 3 |
| `search.h / .cpp` | Search by ID/destination/sender, summary report | Member 4 |
| `menu.h / .cpp` | All menus, input validation, ties modules together | Member 5 |
| `fileio.h / .cpp` | Save/load all data to text files | Shared |

---

## Features

- **Interactive Menu** — nested menus with input validation at every level
- **Package Management** — add, remove, update status, display all
- **Priority Queue** — Express packages processed before Standard (bubble sort)
- **Truck Capacity** — prevents overloading; dispatching marks packages as Delivered
- **Search** — find by Tracking ID (exact), Destination (partial), Sender (partial)
- **Reports** — summary of all packages and trucks, delivered packages list
- **File Persistence** — data saved on exit, loaded on startup

---

## Contribution

| Member | Name | Matric No | Module |
|---|---|---|---|
| 1 | *(Member 1 name)* | *(Matric)* | Data Intake & Validation (`intake.cpp`) |
| 2 | *(Member 2 name)* | *(Matric)* | Ordering & Prioritisation (`priority.cpp`) |
| 3 | *(Member 3 name)* | *(Matric)* | Resource & Capacity Handling (`capacity.cpp`) |
| 4 | 白开水 | *(Matric)* | Search & Reporting (`search.cpp`) |
| 5 | 白开水 | *(Matric)* | Menu System & Integration (`menu.cpp`) |

*(Fill in actual names and matric numbers before submission)*
