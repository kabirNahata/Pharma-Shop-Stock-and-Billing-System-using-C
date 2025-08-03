# Pharma-Shop-Stock-and-Billing-System-using-C

Pharma Shop Stock and Billing System (C Project)
================================================

Objective:
-------------
This is a simple console-based management system for a pharmaceutical shop. It allows users to:

- Log in as staff
- Manage medicine stock (add, update, delete, view)
- Generate and save customer bills
- Log actions with timestamps
- View reports (stock, daily bills, search)
- Display shop info (logo, name, address)

Technologies Used:
------------------------
- Language: C (GCC compatible)
- File I/O for data persistence
- Structs for data models
- Modular code with header and source files

Project Folder Structure:
-----------------------------
/pharma_project/
├── main.c<br />
├── login.c / login.h<br />
├── pharma.c / pharma.h<br />
├── stock.c / stock.h<br />
├── billing.c / billing.h<br />
├── logs.c / logs.h<br />
├── report.c / report.h<br />
├── structs.h<br />
├── users.txt // Pre-added users<br />
├── stock.txt // Medicine inventory<br />
├── bill.txt // Billing history<br />
├── logs.txt // Logs user actions<br />
├── pharma_info.txt // Shop info (name, address, logo)<br />
├── README.txt // This file


Compilation Instructions:
-----------------------------
Make sure you're in the `pharma_project` directory, then compile all `.c` files together using:

gcc main.c login.c pharma.c stock.c billing.c logs.c report.c -o pharma_app

To run the app:

./pharma_app   # On Linux/Mac<br />
pharma_app.exe # On Windows
