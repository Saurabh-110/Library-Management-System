#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

// Structure to represent a book
struct Book
{
    string title;
    string author;
    string isbn;
    int copies;
};

// Structure to represent a member
struct Member
{
    string name;
    string memberId;
    map<string, string> borrowedBooks; // ISBN -> Borrow Date
};

// Class for Library Management System
class Library
{
private:
    map<string, Book> books;     // ISBN -> Book details
    map<string, Member> members; // Member ID -> Member details

    // Helper function to format output
    void printLine(char c, int n)
    {
        for (int i = 0; i < n; i++)
            cout << c;
        cout << endl;
    }

    // Helper function to parse date
    bool parseDate(const string &dateStr, struct tm &tm)
    {
        istringstream ss(dateStr);
        ss >> get_time(&tm, "%Y-%m-%d");
        return !ss.fail();
    }

    // Helper function to calculate due date
    string calculateDueDate(const string &borrowDate)
    {
        struct tm tm = {};
        if (!parseDate(borrowDate, tm))
        {
            cerr << "Error: Invalid date format." << endl;
            return "";
        }
        tm.tm_mday += 14; // Add 14 days
        if (mktime(&tm) == -1)
        {
            cerr << "Error: Unable to calculate due date." << endl;
            return "";
        }
        char dueDate[11];
        if (strftime(dueDate, sizeof(dueDate), "%Y-%m-%d", &tm) == 0)
        {
            cerr << "Error: Unable to format due date." << endl;
            return "";
        }
        return string(dueDate);
    }

public:
    // Add a new book
    void addBook()
    {
        Book newBook;
        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, newBook.title);
        cout << "Enter author: ";
        getline(cin, newBook.author);
        cout << "Enter ISBN: ";
        cin >> newBook.isbn;
        cout << "Enter number of copies: ";
        cin >> newBook.copies;

        if (books.find(newBook.isbn) != books.end())
        {
            books[newBook.isbn].copies += newBook.copies;
            cout << "Book already exists. Updated copies.\n";
        }
        else
        {
            books[newBook.isbn] = newBook;
            cout << "Book added successfully!\n";
        }
    }

    // Add a new member
    // void addMember()
    // {
    //     Member newMember;
    //     cout << "Enter member name: ";
    //     cin.ignore();
    //     getline(cin, newMember.name);
    //     cout << "Enter member ID: ";
    //     cin >> newMember.memberId;

    //     if (members.find(newMember.memberId) != members.end())
    //     {
    //         cout << "Member ID already exists.\n";
    //     }
    //     else
    //     {
    //         members[newMember.memberId] = newMember;
    //         cout << "Member added successfully!\n";
    //     }
    // }
    void addMember()
    {
        Member newMember;
        cout << "Enter member name: ";
        cin.ignore();
        getline(cin, newMember.name);
        cout << "Enter member ID: ";
        cin >> newMember.memberId;

        // Validate Member ID format
        if (newMember.memberId.substr(0, 3) != "USR" || newMember.memberId.size() < 4)
        {
            cout << "Error: Member ID must start with 'USR' and be followed by numbers.\n";
            return;
        }

        if (members.find(newMember.memberId) != members.end())
        {
            cout << "Member ID already exists.\n";
        }
        else
        {
            members[newMember.memberId] = newMember;
            cout << "Member added successfully!\n";
        }
    }
    // void addMember()
    // {
    //     Member newMember;
    //     cout << "Enter member name: ";
    //     cin.ignore();
    //     getline(cin, newMember.name);
    //     cout << "Enter member ID (e.g., 21MI33020): ";
    //     cin >> newMember.memberId;

    //     // Validate Member ID
    //     if (newMember.memberId.size() != 9)
    //     {
    //         cout << "Error: Member ID must be exactly 9 characters long.\n";
    //         return;
    //     }

    //     string year = newMember.memberId.substr(0, 2);
    //     string department = newMember.memberId.substr(2, 2);
    //     string courseCode = newMember.memberId.substr(4, 3);
    //     string uniqueId = newMember.memberId.substr(7, 2);

    //     // Validate Year
    //     if (!isdigit(year[0]) || !isdigit(year[1]))
    //     {
    //         cout << "Error: Year must be a two-digit number.\n";
    //         return;
    //     }

    //     // Validate Department
    //     vector<string> validDepartments = {"MI", "CS", "ECE", "ME", "EE"};
    //     if (find(validDepartments.begin(), validDepartments.end(), department) == validDepartments.end())
    //     {
    //         cout << "Error: Invalid department code. Valid codes are: MI, CS, ECE, ME, EE.\n";
    //         return;
    //     }

    //     // Validate Course Code
    //     vector<string> validCourseCodes = {"100", "310", "330"};

    //     if (find(validCourseCodes.begin(), validCourseCodes.end(), courseCode) == validCourseCodes.end())
    //     {
    //         cout << "Error: Invalid course code. Valid codes are: 100 (B.Tech), 310 (5-year dual), 330 (dual with specialization).\n";
    //         return;
    //     }

    //     // Check if Member ID already exists
    //     if (members.find(newMember.memberId) != members.end())
    //     {
    //         cout << "Error: Member ID already exists.\n";
    //         return;
    //     }

    //     // Add Member
    //     members[newMember.memberId] = newMember;
    //     cout << "Member added successfully!\n";
    // }

    // Display all books
    void displayBooks()
    {
        printLine('-', 50);
        cout << left << setw(15) << "ISBN" << setw(20) << "Title" << setw(15) << "Author" << "Copies" << endl;
        printLine('-', 50);
        for (const auto &entry : books)
        {
            const Book &book = entry.second;
            cout << left << setw(15) << book.isbn << setw(20) << book.title << setw(15) << book.author << book.copies << endl;
        }
        printLine('-', 50);
    }

    // Display all members
    void displayMembers()
    {
        printLine('-', 40);
        cout << left << setw(20) << "Member ID" << "Name" << endl;
        printLine('-', 40);
        for (const auto &entry : members)
        {
            const Member &member = entry.second;
            cout << left << setw(20) << member.memberId << member.name << endl;
        }
        printLine('-', 40);
    }

    // Borrow a book
    void borrowBook()
    {
        string memberId, isbn, date;
        cout << "Enter member ID: ";
        cin >> memberId;
        if (members.find(memberId) == members.end())
        {
            cout << "Invalid member ID.\n";
            return;
        }

        cout << "Enter book ISBN: ";
        cin >> isbn;
        if (books.find(isbn) == books.end() || books[isbn].copies == 0)
        {
            cout << "Book not available.\n";
            return;
        }

        cout << "Enter borrow date (YYYY-MM-DD): ";
        cin >> date;

        members[memberId].borrowedBooks[isbn] = date;
        books[isbn].copies--;

        string dueDate = calculateDueDate(date);
        if (!dueDate.empty())
        {
            cout << "Book borrowed successfully! Due date: " << dueDate << "\n";
        }
    }

    // Return a book
    void returnBook()
    {
        string memberId, isbn;
        cout << "Enter member ID: ";
        cin >> memberId;
        if (members.find(memberId) == members.end())
        {
            cout << "Invalid member ID.\n";
            return;
        }

        cout << "Enter book ISBN: ";
        cin >> isbn;
        if (members[memberId].borrowedBooks.find(isbn) == members[memberId].borrowedBooks.end())
        {
            cout << "This book was not borrowed by the member.\n";
            return;
        }

        members[memberId].borrowedBooks.erase(isbn);
        books[isbn].copies++;

        cout << "Book returned successfully!\n";
    }

    // Display borrowed books by a member
    void displayBorrowedBooks()
    {
        string memberId;
        cout << "Enter member ID: ";
        cin >> memberId;
        if (members.find(memberId) == members.end())
        {
            cout << "Invalid member ID.\n";
            return;
        }

        Member &member = members[memberId];
        if (member.borrowedBooks.empty())
        {
            cout << "No books borrowed.\n";
            return;
        }

        printLine('-', 50);
        cout << left << setw(15) << "ISBN" << setw(15) << "Borrow Date" << "Due Date" << endl;
        printLine('-', 50);
        for (const auto &entry : member.borrowedBooks)
        {
            string dueDate = calculateDueDate(entry.second);
            if (!dueDate.empty())
            {
                cout << left << setw(15) << entry.first << setw(15) << entry.second << dueDate << endl;
            }
        }
        printLine('-', 50);
    }

    // Reminder for overdue books
    void overdueReminder()
    {
        string currentDate;
        cout << "Enter current date (YYYY-MM-DD): ";
        cin >> currentDate;

        printLine('-', 50);
        cout << "Overdue Books:\n";
        printLine('-', 50);

        for (const auto &memberEntry : members)
        {
            const Member &member = memberEntry.second;
            for (const auto &borrowEntry : member.borrowedBooks)
            {
                string dueDate = calculateDueDate(borrowEntry.second);
                if (!dueDate.empty() && currentDate > dueDate)
                {
                    cout << "Member ID: " << member.memberId << ", Book ISBN: " << borrowEntry.first << ", Due Date: " << dueDate << endl;
                }
            }
        }

        printLine('-', 50);
    }
};

// Main function
int main()
{
    Library library;
    int choice;

    do
    {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Display Books\n";
        cout << "4. Display Members\n";
        cout << "5. Borrow Book\n";
        cout << "6. Return Book\n";
        cout << "7. Display Borrowed Books\n";
        cout << "8. Overdue Reminder\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            library.addBook();
            break;
        case 2:
            library.addMember();
            break;
        case 3:
            library.displayBooks();
            break;
        case 4:
            library.displayMembers();
            break;
        case 5:
            library.borrowBook();
            break;
        case 6:
            library.returnBook();
            break;
        case 7:
            library.displayBorrowedBooks();
            break;
        case 8:
            library.overdueReminder();
            break;
        case 9:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
