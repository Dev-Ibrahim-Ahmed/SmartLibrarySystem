#include <iostream>
#include "Book.h"
#include "Person.h"
#include "Member.h"
#include "Librarian.h"
#include "DataManager.h"
#include "resizableArray.h"
#include "funcs.h"
#include "menus.h"

using namespace std;

resizableArray<Book> catalog(500);
resizableArray<Person*> users;

void Member::menu() {
    clearConsole();
    int ch;
    while (true) {
        printCentered("Welcome Member " + BOLD + YELLOW + getName() + RESET);
        cout << "\n1. Display Info" << endl;
        cout << "2. Borrow a Book" << endl;
        cout << "3. Return a Book" << endl;
        cout << "4. View Borrowed Books" << endl;
        cout << "5. View Fines" << endl;
        cout << "0. Logout" << endl;

        validate(ch, "Enter choice: ");
        switch (ch) {
            case 1:
                displayInfo();
                break;
            case 2: {
                string q;
                validate(q, "Enter title, author, or ISBN to search: ");
                borrowBook(catalog, q);
                break;
            }
            case 3: {
                string titleOrIsbn;
                validate(titleOrIsbn, "Enter the Book Title or ISBN to return: ");
                returnBook(titleOrIsbn);
                break;
            }
            case 4: {
                displayInfo();
                break;
            }
            case 5: {
                cout << BOLD << "Total fine balance: $" << fines << RESET << endl;
                break;
            }
            case 0:
                clearConsole();
                return;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

void Librarian::menu() {
    clearConsole();
    int ch;
    while (true) {
        cout << "\n=== LIBRARIAN MANAGEMENT ===" << endl;
        cout << "1. Display Info" << endl;
        cout << "2. Add a Book to Catalog" << endl;
        cout << "3. Remove a Book from Catalog" << endl;
        cout << "4. Register a Member" << endl;
        cout << "5. Remove a Member" << endl;
        cout << "6. View Catalog" << endl;
        cout << "7. View Registered Members" << endl;
        cout << "0. Logout" << endl;

        validate(ch, "Enter choice: ");
        switch (ch) {
            case 1:
                displayInfo();
                break;
            case 2:
                addBook(catalog);
                break;
            case 3: {
                string isbn;
                validate(isbn, "Enter ISBN of book to remove: ");
                removeBook(catalog, isbn);
                break;
            }
            case 4:
                addMember(users);
                break;
            case 5: {
                int memberId;
                validate(memberId, "Enter ID of member to remove: ");
                removeMember(users, memberId);
                break;
            }
            case 6:
                displayBooks(catalog);
                break;
            case 7:
                displayMembers(users);
                break;
            case 0:
                clearConsole();
                return;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

bool login_menu() {
    cout << "\n\n";
    printCentered(CYAN + BOLD + boxLine + RESET);
    printCentered(BOLD + "SMART LIBRARY SYSTEM LOG IN" + RESET);
    printCentered(CYAN + BOLD + boxLine + RESET);
    cout << "\n";

    int x;
    while (true) {
        validate(x, BOLD + "Enter ID (or 0 to Exit System): " + RESET);
        if (x == 0) return false;
        if (x < 0) {
            cout << "Invalid ID format." << endl;
            continue;
        }

        Person *p = nullptr;
        for (int i = 0; i < users.size(); ++i) {
            if (users[i] != nullptr && users[i]->getId() == x) {
                p = users[i];
                break;
            }
        }

        if (p == nullptr) {
            cout << "No user found with ID: " << x << endl;
            continue;
        }

        bool loggedIn = false;
        for (int attempts = 0; attempts < 3; ++attempts) {
            string s;
            validate(s, BOLD + "Enter Password: " + RESET);
            if (p->checkPassword(s)) {
                cout << BOLD + GREEN + "Welcome " + p->getName() + "!" + RESET << endl;
                p->menu();
                loggedIn = true;
                break;
            }
            cout << "Incorrect password! Attempts remaining: " << (2 - attempts) << endl;
        }

        if (loggedIn) return true;
        cout << "Too many wrong attempts! Returning to main prompt..." << endl;
        clearConsole();
    }
}

int main() {
    showLoadingMenu("Initializing Program", 1000);
    showLoadingMenu("Initializing Database", 1500);
    DataManager::loadBooks("../data/books.json", catalog);
    DataManager::loadPersons("../data/persons.json", users, catalog);
    showLoadingMenu("starting program", 1500);
    clearConsole();

    bool running = true;
    while (running) {
        running = login_menu();
    }

    cout << "\nSaving system state to storage..." << endl;
    DataManager::saveBooks("../data/books.json", catalog);
    DataManager::savePersons("../data/persons.json", users);

    for (int i = 0; i < users.size(); ++i) {
        delete users[i];
    }

    cout << GREEN << "System shutdown completed successfully." << RESET << endl;
    return 0;
}