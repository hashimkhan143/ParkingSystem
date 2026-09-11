# 🚗 PARKING BLOCK

### `A Dynamic Object-Oriented Parking Management System`

> **Not just a parking lot — a complete playground for C++ OOP, dynamic memory, operator overloading, and resource management.**

---

## 🅿️ Project Overview

**Parking Block** is a console-based parking management system developed in **C++** using advanced **Object-Oriented Programming** concepts.

The system models a collection of parking blocks where every block can have a different number of rows and parking slots. Vehicles can be parked, removed, searched, transferred, merged, and intelligently allocated.

The project goes beyond basic CRUD operations by implementing **dynamic 3D memory structures**, **copy/move constructors**, **operator overloading**, **file handling**, **coordinate-based parking**, and more.

Think of it as:

```text
              🚗
               │
        ┌──────▼──────┐
        │   PARKING   │
        │    BLOCK    │
        └──────┬──────┘
               │
       ┌───────┼────────┐
       ▼       ▼        ▼
     ROW 1   ROW 2    ROW 3
      │││     ││       ││││
      ▼▼▼     ▼▼       ▼▼▼▼
     🚗 ⬜ 🚗  ⬜ 🚗    🚗 🚗 ⬜ 🚗
```

---

# ✨ Features

### 🚘 Vehicle Management

* Park a vehicle in a specific row and slot
* Remove a vehicle
* Search for a vehicle
* Remove a specific vehicle using `-=`
* Automatically detect occupied/empty slots

### 🏢 Parking Block Management

* Create parking blocks dynamically
* Different number of slots per row
* Add new rows
* Add new slots
* Increase/decrease row capacity
* Empty an entire row
* Empty an entire parking block

### 🧠 Smart Parking

The system includes a **smart allocation mechanism** that searches for an available slot and calculates its distance from the block's coordinates.

```cpp
blocks[b - 1] += vehicle;
```

Instead of manually selecting a slot, the system can determine a suitable available location automatically.

---

# 🧬 OOP Concepts Demonstrated

This project was designed to demonstrate several important C++ OOP concepts.

| Concept                 | Implementation                        |
| ----------------------- | ------------------------------------- |
| 🏛️ Classes & Objects   | `ParkingBlock`                        |
| 🔐 Encapsulation        | Private parking data                  |
| 🧹 Destructor           | Releases dynamically allocated memory |
| 📋 Copy Constructor     | Deep-copy support                     |
| 🔄 Copy Assignment      | `operator=`                           |
| ⚡ Move Constructor      | Efficient resource transfer           |
| 🚚 Move Assignment      | Ownership transfer                    |
| ➕ Operator Overloading  | `+`, `+=`, `++`                       |
| ➖ Operator Overloading  | `-`, `-=`, `--`                       |
| ⚖️ Comparison Operators | `==`, `!=`, `>`, `<`                  |
| 📥 Stream Operators     | `<<`, `>>`                            |
| 🧠 Dynamic Memory       | `char***`, dynamic arrays             |
| 📂 File Handling        | `ifstream`                            |
| 🤝 Friend Functions     | Stream operators                      |
| 📐 Coordinate System    | X/Y block positions                   |

---

# 🧩 Data Structure

At the heart of the project is a dynamically allocated **3-dimensional character structure**:

```cpp
char*** slots;
```

Conceptually:

```text
ParkingBlock
     │
     ▼
   Rows
     │
 ┌───┼────┐
 ▼   ▼    ▼
Row Row  Row
 │   │    │
 ▼   ▼    ▼
Slots
 │
 ├── "EMPTY"
 ├── "ABC123"
 ├── "XYZ789"
 └── "CAR456"
```

Each row can contain a **different number of slots**, making the structure dynamic rather than a fixed-size 2D array.

---

# ♻️ Memory Management

One of the major goals of this project is managing dynamically allocated memory manually.

The system allocates:

```cpp
char*** slots;
int* slotsPerRow;
```

and properly manages nested allocations.

The destructor releases:

```text
Vehicle strings
      ↓
Slot arrays
      ↓
Row arrays
      ↓
slots
      ↓
slotsPerRow
```

This makes the project a practical demonstration of **manual memory management in C++**.

---

# 🔁 Copy vs Move Semantics

The project implements both **copy semantics** and **move semantics**.

### 📋 Copy

The copy constructor creates a separate representation of another parking block.

```cpp
ParkingBlock(const ParkingBlock& other);
```

Similarly, copy assignment is implemented using:

```cpp
operator=(const ParkingBlock& other);
```

### ⚡ Move

Move operations transfer ownership of dynamically allocated resources instead of duplicating them.

```cpp
ParkingBlock(ParkingBlock&& other);
```

and:

```cpp
operator=(ParkingBlock&& other);
```

Conceptually:

```text
COPY

Block A ───────► duplicate resources ───────► Block B


MOVE

Block A ───────► transfer ownership ───────► Block B
                  │
                  └── A becomes empty/null
```

---

# 🪄 Operator Overloading

One of the most interesting parts of the project is the use of overloaded operators to make parking operations feel natural.

### ➕ Merge Blocks

```cpp
ParkingBlock result = block1 + block2;
```

Combines vehicles from two blocks into a new block.

---

### ➖ Subtract Vehicles

```cpp
ParkingBlock result = block1 - block2;
```

Removes vehicles from one block based on another block.

---

### 🚗 Add a Vehicle

```cpp
block += vehicle;
```

Automatically attempts to smart-allocate the vehicle.

---

### 🗑️ Remove a Vehicle

```cpp
block -= vehicle;
```

Searches for the specified vehicle and removes it.

---

### ➕ Add a Row

```cpp
++block;
```

Adds a new row to the parking block.

---

### ➖ Remove Last Row

```cpp
--block;
```

Removes the last row **only when it is empty**.

---

### ⚖️ Compare Blocks

```cpp
if (block1 > block2)
```

Compares the number of occupied parking slots.

---

# 📍 Coordinate-Based Parking

Each parking block stores an X/Y coordinate:

```cpp
float x_coordinate;
float y_coordinate;
```

Coordinates can be assigned using:

```cpp
setCoordinates(x, y);
```

The smart parking algorithm uses these coordinates when calculating the distance of available slots.

---

# 🧠 Smart Allocation

The smart parking feature scans available slots and calculates their distance from the block's origin.

The basic idea is:

```text
           Parking Block
                📍
                │
       ┌────────┼────────┐
       │        │        │
      ⬜       🚗       ⬜
       │                 │
       ▼                 ▼
    Distance          Distance
       │                 │
       └────────┬────────┘
                ▼
          Best available
              slot
```

A vehicle can therefore be inserted without manually specifying its row and slot.

---

# 📂 File Handling

The project can load parking block information from files using:

```cpp
ifstream
```

The loading process creates an array of `ParkingBlock` objects and populates their structure from file data.

There is also support for loading **block coordinates** from a separate file.

---

# 🎮 Console Menu

Once the blocks are initialized, the program provides a menu-driven interface:

```text
╔══════════════════════════════════════════╗
║          🚗 PARKING SYSTEM MENU          ║
╠══════════════════════════════════════════╣
║  0  Initialize                           ║
║  1  Park a vehicle                       ║
║  2  Remove a vehicle                     ║
║  3  Display full system                  ║
║  4  Resize slots                         ║
║  5  Search for a vehicle                 ║
║  6  Empty a row                          ║
║  7  Empty a block                        ║
║  8  Transfer vehicles                    ║
║  9  Smart park                           ║
║ 10  Remove vehicles of another block    ║
║ 11  Remove specific vehicle              ║
║ 12  Add row                              ║
║ 13  Remove last empty row                ║
║ 14  Compare blocks                       ║
║ 15  Merge blocks                         ║
║ 16  Subtract blocks                      ║
║ 17  Load block coordinates               ║
║ 18  Merge vehicles                       ║
║ 19  Exit                                 ║
╚══════════════════════════════════════════╝
```

---

# 🛠️ Technologies

```text
Language       → C++
Paradigm       → Object-Oriented Programming
Compiler       → Any C++ compiler supporting C++11+
Libraries      → iostream
                 fstream
                 cmath
Memory Model   → Dynamic Memory Allocation
Interface      → Console / CLI
```

---

# 🚀 Getting Started

## 1️⃣ Clone the Repository

```bash
git clone https://github.com/your-username/parking-block.git
```

## 2️⃣ Enter the Project

```bash
cd parking-block
```

## 3️⃣ Compile

Using `g++`:

```bash
g++ assignment3oop.cpp -o parking
```

## 4️⃣ Run

### Windows

```bash
parking.exe
```

### Linux / macOS

```bash
./parking
```

---

# 🧪 Example Workflow

A typical session might look like:

```text
Enter number of parking blocks: 2

Initializing Block 1
Enter number of rows: 3

Enter number of slots for 0th row: 4
Enter number of slots for 1th row: 3
Enter number of slots for 2th row: 5

Enter coordinates (x y): 10 20
```

Then a vehicle can be parked:

```text
Block Row Slot: 1 2 3
Vehicle number: ABC12345

Vehicle parked
```

And searched later:

```text
Block: 1
Vehicle number: ABC12345

Found at Row 2 Slot 3
```

---

# 🏗️ Project Architecture

```text
                 ┌───────────────────────┐
                 │     ParkingBlock      │
                 └───────────┬───────────┘
                             │
          ┌──────────────────┼──────────────────┐
          │                  │                  │
          ▼                  ▼                  ▼
    Memory System       Vehicle System      Block System
          │                  │                  │
      char***           Park / Remove      Add / Remove
      int*               Search             Resize
      RAII-style         Transfer           Merge
      cleanup            Smart Park         Empty
          │                  │                  │
          └──────────────────┼──────────────────┘
                             │
                             ▼
                  ┌─────────────────────┐
                  │   Operator System   │
                  ├─────────────────────┤
                  │ +  -  +=  -=        │
                  │ ++ --               │
                  │ == != > <           │
                  │ << >>               │
                  └─────────────────────┘
```

---

# 🎯 Learning Objectives

This project provides hands-on practice with:

* Understanding classes and objects
* Encapsulation and private data
* Dynamic memory allocation
* Multi-level pointers
* Deep copying
* Copy constructors
* Copy assignment operators
* Move constructors
* Move assignment operators
* Destructors
* Friend functions
* Operator overloading
* File input/output
* Dynamic data structures
* Object lifetime and ownership
* Resource management

---

# 📌 Project Highlights

> ### Why this project stands out

**01 — Dynamic Structure**
No fixed-size parking layout. Rows and slots can be dynamically created and resized.

**02 — Manual Memory Management**
The project directly works with dynamically allocated memory and nested pointers.

**03 — Rule-Based Operations**
Operations such as removing a row require the row to satisfy certain conditions.

**04 — Operator-Based Interface**
Common parking operations are represented using overloaded C++ operators.

**05 — Smart Allocation**
Vehicles can be automatically assigned to available parking positions.

**06 — Object Semantics**
Copy and move operations demonstrate how C++ objects manage resources.

---

# 🗂️ Main Class

The entire parking system revolves around:

```cpp
class ParkingBlock
```

Its responsibilities include:

```text
ParkingBlock
│
├── Construction
├── Copy / Move
├── Memory Allocation
├── Vehicle Parking
├── Vehicle Removal
├── Vehicle Search
├── Row Management
├── Slot Management
├── Block Management
├── Smart Allocation
├── Vehicle Transfer
├── Block Merging
├── Block Subtraction
├── Comparisons
├── File Streaming
└── Resource Cleanup
```

---

# 🔮 Possible Future Improvements

The current console implementation could be extended into a complete parking application with:

* 🖥️ Graphical User Interface
* 🗺️ Visual parking map
* 🪪 Vehicle owner information
* 🕒 Entry and exit timestamps
* 💰 Parking fee calculation
* 📊 Occupancy statistics
* 🔍 Faster vehicle searching
* 🧵 Multi-user support
* 💾 Database integration
* 🌐 Web-based parking dashboard
* 📱 Mobile parking interface

---

# 👨‍💻 Author

**Muhammad Hashim Khan**

> Built as an Object-Oriented Programming project to explore dynamic memory, resource management, and advanced C++ class design.

---

## ⭐ If You Like It

If this project helped you understand C++ OOP, consider giving the repository a ⭐.

```text
       🚗
      /██\
 ┌───┴────┴───┐
 │  PARK HERE  │
 └─────────────┘

   Code • Park • Manage
```

### `Made with C++ & a lot of pointers.`
