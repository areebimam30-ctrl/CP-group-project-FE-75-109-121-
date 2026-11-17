# CP-group-project-FE-75-109-121-
Areeb(cs-075), Meerab(cs-109), Ahmed(cs-121)
# Cafeteria Management System

## Overview

The Cafeteria Management System is a menu-driven C programming project developed as part of the Computer Programming course at NED University of Engineering and Technology.

The purpose of this project is to manage basic cafeteria operations through a simple console-based application. It allows users to maintain food records, manage available stock, process customer orders, and calculate bills.

The system uses file handling to preserve menu information and order records so that data remains available when the program is run again.

## Features

- **Add Food Items:** Add new food items by entering their ID, name, price, and available quantity.
- **Display Food Items:** View the available cafeteria menu with item details.
- **Search Food Items:** Find a particular food item using its ID.
- **Update Food Items:** Modify the name, price, or quantity of an existing item.
- **Delete Food Items:** Remove food records from the menu.
- **Take Customer Orders:** Select food items and specify quantities to create customer orders.
- **Calculate Bills:** Calculate individual item subtotals and the total customer bill.
- **Stock Management:** Check available quantities before accepting an order and update stock after a successful purchase.
- **Order Records:** Store and display previous customer orders.
- **File Handling:** Save and load menu and order information using files.
- **Dynamic Memory Allocation:** Allocate and resize memory as the number of menu items and orders changes.

## Technologies Used

- Programming Language: C
- Compiler: GCC
- Development Environment: Visual Studio Code
- Version Control: Git and GitHub

## Concepts Implemented

The project demonstrates the practical use of fundamental C programming concepts, including:

- Variables and data types
- Operators and expressions
- Conditional statements
- Loops
- Functions and modular programming
- Arrays and strings
- Structures
- Pointers
- Dynamic memory allocation (`malloc`, `realloc`, and `free`)
- File handling (`fopen`, `fread`, `fwrite`, `fprintf`, and `fscanf`)

## Data Storage

The system uses files to maintain records between program executions:

- `menu.dat` – Stores food menu records in binary format.
- `orders.txt` – Stores customer order records in text format.

Menu information is loaded when the program starts, while changes and customer orders are saved to their respective files.

## How to Run the Project

### Requirements
- GCC compiler
- Visual Studio Code or another C development environment

### Steps

1. Clone or download this repository.
2. Open the project folder in Visual Studio Code.
3. Open the terminal in the project directory.
4. Compile the C source files using GCC.
5. Run the generated executable.

For a single-file version of the project, the commands are:

```bash
gcc main.c -o cafeteria
```

On Windows:

```bash
.\cafeteria.exe
```

If the project uses multiple C source files, compile all required `.c` files together.

## Project Structure

The project contains C source code files and the data files used to store cafeteria records. The exact file structure depends on the final integrated version of the project.

## Limitations

- The application runs in a command-line interface.
- It does not use a graphical user interface or database.
- It is designed for basic cafeteria record management rather than a complete commercial cafeteria system.

This project was developed as a group assignment to apply the concepts learned in C programming to a practical management-system scenario.
