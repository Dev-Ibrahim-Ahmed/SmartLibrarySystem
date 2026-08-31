#include "Librarian.h"
#include "funcs.h"
#include <iostream>

Librarian::Librarian() : Person(), employeeId("") {}

Librarian::Librarian(int id, const string& name, const string& password, const string& employeeId)
    : Person(id, name, password), employeeId(employeeId) {}

void Librarian::addBook(resizableArray<Book> &catalog) {
    Book book;
    cin >> book;
    catalog.addItem(book);
    cout << "Book added successfully to catalog.\n";
}

void Librarian::removeBook(resizableArray<Book> &catalog, const string& isbn) {
    for (int i = 0; i < catalog.size(); i++) {
        if (catalog[i].getISBN() == isbn) {
            catalog.removeItemAt(i);
            cout << "Book with ISBN " << isbn << " removed successfully.\n";
            return;
        }
    }
    cout << "Book with ISBN " << isbn << " not found in catalog.\n";
}

void Librarian::addMember(resizableArray<Person *>& users) {
    int id = 0;
    while (true) {
        validate(id, "Enter Member ID: ");
        if (id > 0) break;
        cout << "Invalid ID. Must be greater than 0.\n";
    }

    string name, password;
    validate(name, "Enter Name: ");
    validate(password, "Enter Password: ");

    users.addItem(new Member(id, name, password));
    cout << "Member registered successfully.\n";
}

void Librarian::removeMember(resizableArray<Person *>& users, int memberId) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i] != nullptr && users[i]->getId() == memberId && users[i]->getType() == "Member") {
            delete users[i];
            users.removeItemAt(i);
            cout << "Member ID " << memberId << " removed successfully.\n";
            return;
        }
    }
    cout << "Member with ID " << memberId << " not found.\n";
}

void Librarian::displayBooks(const resizableArray<Book>& catalog) const {
    cout << "\n===== CATALOG BOOKS (" << catalog.size() << ") =====\n";
    for (int i = 0; i < catalog.size(); i++) {
        cout << "[" << (i + 1) << "] ";
        catalog[i].showData();
    }
}

void Librarian::displayMembers(const resizableArray<Person*>& users) const {
    cout << "\n===== REGISTERED MEMBERS =====\n";
    int count = 0;
    for (int i = 0; i < users.size(); i++) {
        if (users[i] != nullptr && users[i]->getType() == "Member") {
            users[i]->displayInfo();
            count++;
        }
    }
    if (count == 0) cout << "No members registered.\n";
}

string Librarian::getEmployeeId() const { return employeeId; }
void Librarian::setEmployeeId(const string& newEmployeeId) { employeeId = newEmployeeId; }

void Librarian::displayInfo() const {
    cout << "[Librarian Profile] ID: " << getId()
         << " | Name: " << getName()
         << " | Employee ID: " << employeeId << endl;
}

void Librarian::displayStatistics() const {
    cout << "Librarian Name: " << getName() << endl;
    cout << "Employee ID: " << employeeId << endl;
}