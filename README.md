# Library Management System in C++

## 1. Overview

This project is a comprehensive and scalable Library Management System developed in C++. It is designed using Object-Oriented Programming (OOP) principles to streamline and automate library operations. The system leverages robust C++ data structures like `std::map` for efficient management of books and member records.

The application provides a console-based interface for librarians to manage inventory, handle member transactions, and monitor borrowing activities with minimal manual intervention.

## 2. Features

This system includes a variety of features designed for efficient library management:

* **Dynamic Inventory Management**: Tracks the availability of books in real-time, automatically updating the number of copies when a book is borrowed or returned.
* **Member Management**: Allows for the addition and display of library members. It supports unique member ID formats. The current implementation validates that member IDs start with "USR".
* **Borrowing and Returning**: Facilitates the process of issuing and returning books, linking transactions to specific member profiles.
* **Automated Due-Date Calculation**: Automatically calculates the due date for a borrowed book, which is set to 14 days from the borrowing date.
* **Overdue Reminders**: Includes a feature to list all books that are past their due date, helping librarians manage timely returns.
* **Efficient Data Handling**: Uses `std::map` for fast lookups of books (by ISBN) and members (by Member ID), ensuring seamless record management.
* **Error Handling**: Prevents invalid operations, such as borrowing an unavailable book or using a non-existent member ID, through robust validation checks.
* **User-Friendly Console Interface**: A simple and intuitive menu-driven interface makes the system easy to operate.

## 3. How to Compile and Run

You will need a C++ compiler (like G++) to run this project.

1.  **Save the Code**: Save the provided C++ code as `libraryManagement_01.cpp`.
2.  **Compile**: Open a terminal or command prompt and run the following command:
    ```sh
    g++ libraryManagement_01.cpp -o library_management
    ```
3.  **Run**: Execute the compiled program:
    ```sh
    ./library_management
    ```

## 4. How to Use

Once the program is running, you will see a menu with the following options:

1.  **Add Book**: Prompts for the book's title, author, ISBN, and the number of copies. If the book (based on ISBN) already exists, it updates the copy count.
2.  **Add Member**: Prompts for the member's name and a unique Member ID. The Member ID must begin with "USR".
3.  **Display Books**: Shows a formatted list of all books in the library, including their ISBN, title, author, and available copies.
4.  **Display Members**: Shows a list of all registered members with their IDs and names.
5.  **Borrow Book**: Asks for a Member ID and a book ISBN. It then requests the borrow date in `YYYY-MM-DD` format and calculates the due date.
6.  **Return Book**: Asks for the Member ID and the ISBN of the book being returned to update the library's inventory.
7.  **Display Borrowed Books**: For a given Member ID, it displays all books currently borrowed by that member, along with their borrow and due dates.
8.  **Overdue Reminder**: Asks for the current date (`YYYY-MM-DD`) and lists all books that are overdue across all members.
9.  **Exit**: Terminates the program.
