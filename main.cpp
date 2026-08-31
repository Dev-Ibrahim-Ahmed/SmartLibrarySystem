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
resizableArray<Member>members;
void Member::menu() {
    clearConsole();
    int ch;
    while (true) {
        printCentered("Welcome Member " + BOLD + YELLOW + getName());
        cout << "Enter 1 to display your info" << endl;
        cout << "Enter 2 to Borrow a Book" << endl;
        cout << "Enter 3 to return a Book" << endl;
        cout << "Enter 4 to view Borrowed Books" << endl;
        cout << "Enter 5 to view fines" << endl;
        cout << "Enter 0 to Exit" << endl;
        validate(ch);
        switch (ch) {
            case 1 :
                displayInfo();
                break;
            case 2 : {
                string q;
                cout << "Enter your query : ";
                validate(q);
                borrowBook(catalog , q);
                break;
            }
            case 3 : {
                string isbn;
                cout << "Enter the book ISBN : ";
                validate(isbn);
                returnBook(isbn);
                break;
            }
            case 4 : {
                if (Borrowed == 0) {
                    cout << "No borrowed books." << endl;
                } else {
                    for (int i = 0; i < Borrowed; i++) {
                        if (books[i] != nullptr) {
                            cout << i + 1 << "  - " << books[i]->getTitle() << endl;
                        }
                    }
                }
                break;
            }
            case 5 : {
                cout << BOLD << "you have to pay a total of : " << fines << endl;
            }
            case 0 :
                return;

            default :
                cout << "Invalid choice!" << endl;
        }
    }
}

void Librarian::menu() {
    clearConsole();
    int ch;
    while (true) {
        cout << "Enter 1 to display your Info" << endl;
        cout << "Enter 2 to add a Book to the category" << endl;
        cout << "Enter 3 to remove a Book from the category" << endl;
        cout << "Enter 4 to register a member" << endl;
        cout << "Enter 5 to remove a member" << endl;
        cout << "Enter 6 to view the category" << endl;
        cout << "Enter 7 to view the members" << endl;
        cout << "Enter 0 to Exit" << endl;
        validate(ch , "Enter your choice : ");
        switch (ch) {
            case 1 : {
                displayInfo();
                break;
            }
            case 2 : {
                addBook(catalog);
            }
        }
    }
}

void login_menu() {
    cout << "\n\n";
    printCentered(CYAN + BOLD + boxLine + RESET);
    printCentered(BOLD + "SMART LIBRARY SYSTEM" + RESET);
    printCentered(CYAN + BOLD + boxLine + RESET);
    cout << "\n";

    int x;
    Person *p = nullptr;
    while (true) {
        validate(x , BOLD + "Enter your id : " + RESET);
        if (x <= 0)continue;
        cout << "Invalid Input";
        for (int i = 0; i < users.size(); ++i) {
            if (users[i]->getId() == x) {
                p = users[i];
            }
        }
        if (p != nullptr)break;
        cout << "No user with this ID was found" << endl;
        for (int i = 0; i < 3; ++i) {
            string s;
            validate(s , BOLD + "Enter your password : " + RESET);
            if (p->checkPassword(s)) {
                cout << BOLD + GREEN + "Welcome " + p->getName() << RESET;
                p->menu();
                return;
            }
            cout << "wrong password!" << endl;
        }
        cout << "Too many wrong attempts!!!" << endl;
        clearConsole();
    }
}



int main() {
    showLoadingMenu("Initializing Program" , 2000);
    showLoadingMenu("Initializing Database", 1000);
    DataManager::loadBooks("../data/books.json", catalog);
    showLoadingMenu("Loading Data" , 1500);
    DataManager::loadPersons("../data/persons.json", users, catalog);
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getType() == "Member") {
            Member m(users[i]->getId() , users[i]->getName() , users[i]->getPassword() , users[i]->getLimit());
            for (int j = 0; j < users[i]->getBorrowed(); ++i) {
                *m[i] = *(*users[i])[i];
            }
            members.addItem(m);
        }
    }
    cout << "\033[H\033[2J" << endl;




}
