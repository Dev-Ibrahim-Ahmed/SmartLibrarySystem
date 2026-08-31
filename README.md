# Smart Library Management System

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++17" />
  <img src="https://img.shields.io/badge/CMake-3.16+-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake" />
  <img src="https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge" alt="Build Status" />
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge" alt="License: MIT" />
</p>

A modular, console-based library automation system written in C++17 using Object-Oriented Programming principles, a custom dynamic array template, and JSON file persistence.

---

## Overview

The Smart Library Management System automates day-to-day library operations. It provides role-based authentication for **Members** and **Librarians**, book inventory tracking with borrow/return workflows, late fine calculation, catalog search/sort, and persistent JSON storage.

---

## Features

### Authentication & Roles
- Secure login using User ID and Password.
- Automatic routing to Member or Librarian specific dashboards.
- Password verification with retry limits.

### Member Operations
- View personal profile, borrowed books list, and fine balance.
- Multi-criteria search across Title, Author, Category, or ISBN (`BookFind`).
- Borrow available books (enforces limit of 3 books per member).
- Return books with automatic late fine calculation ($2.00 / day).

### Librarian Operations
- Add new books to catalog with initial copy counts.
- Remove books from catalog by ISBN.
- Register new members and remove existing accounts.
- Display full catalog inventory and registered members list.
- View real-time statistics (total titles, copies, active loans).

### JSON Persistence
- Automatic loading and saving with `data/books.json` and `data/persons.json`.
- Automatic path fallback to locate data files whether launched from root or `build/`.

---

## OOP Concepts Applied

- **Abstract Base Class (`Person`)**: Defines the base user interface with pure virtual functions (`displayInfo()`, `menu()`, `getType()`).
- **Inheritance (`Member`, `Librarian`)**: Derived classes inherit from `Person` and implement role-specific operations.
- **Polymorphism**: Uses base class pointers (`Person*`) inside a single container to dynamically invoke derived methods and menus at runtime.
- **Encapsulation**: Attributes are protected/private and accessed through validated getters, setters, and operator overloads (`++`, `--`, `>>`, `==`, `>`).
- **Custom Template Container (`resizableArray<T>`)**: Generic dynamic array implementing heap reallocation, deep copy constructor, assignment operator, and destructor (Rule of Three), without relying on `std::vector`.

---

## Project Structure

```text
SmartLibrary/
├── CMakeLists.txt
├── README.md
├── main.cpp
├── data/
│   ├── books.json
│   └── persons.json
├── include/
│   ├── Book.h
│   ├── Person.h
│   ├── Member.h
│   ├── Librarian.h
│   ├── DataManager.h
│   ├── funcs.h
│   ├── menus.h
│   ├── resizableArray.h
│   └── json.hpp
└── src/
    ├── Book.cpp
    ├── Person.cpp
    ├── Member.cpp
    ├── Librarian.cpp
    ├── DataManager.cpp
    ├── funcs.cpp
    └── menus.cpp
```

---

## How to Build and Run

### Prerequisites
- GCC / MinGW (C++17 support) or CMake 3.16+

### 1. Compile with g++
```powershell
g++ -std=c++17 -Wall -Wextra -Iinclude -o SmartLibrarySystem.exe main.cpp src/*.cpp
```

### 2. Run
```powershell
.\SmartLibrarySystem.exe
```
*(On Linux / macOS: `./SmartLibrarySystem.exe`)*

### 3. Alternative: Build with CMake
```powershell
cmake -B build
cmake --build build
.\build\SmartLibrarySystem.exe
```

---

## Sample Credentials

| Role | ID | Password | Name |
|---|---|---|---|
| **Librarian** | `1` | `admin2024` | Ibrahim Al Abd |
| **Librarian** | `2` | `pass2026` | Dr. Mona Tarek |
| **Member** | `101` | `1234` | Ahmed Abdoo |
| **Member** | `102` | `5678` | Sondos Ahmed |
| **Member** | `103` | `9012` | Omar Khaled |

---

## License

This project is licensed under the MIT License.
