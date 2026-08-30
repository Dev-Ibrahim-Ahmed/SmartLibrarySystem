#include "Librarian.h"

Librarian::Librarian() : Person(), employeeId("") {}

Librarian::Librarian(int id, const string &name, const string &password, const string &employeeId)
    : Person(id, name, password), employeeId(employeeId) {}

void Librarian::addBook(Book* book) {
    if (book == nullptr) {
        cout << "Invalid book." << endl;
        return;
    }
    books.addItem(book);
    cout << "Book added successfully." << endl;
}

void Librarian::removeBook(Book* book) {
    if (book == nullptr) {
        cout << "Invalid book." << endl;
        return;
    }
    for (int i = 0; i < books.size(); i++) {
        if (books[i] == book) {
            cout << "Book removed: " << books[i]->getTitle() << endl;
            return;
        }
    }
    cout << "Book not found." << endl;
}

void Librarian::addMember(Member* member) {
    if (member == nullptr) {
        cout << "Invalid member." << endl;
        return;
    }
    members.addItem(member);
    cout << "Member added successfully." << endl;
}

void Librarian::removeMember(Member* member) {
    if (member == nullptr) {
        cout << "Invalid member." << endl;
        return;
    }
    for (int i = 0; i < members.size(); i++) {
        if (members[i] == member) {
            cout << "Member removed: " << members[i]->getName() << endl;
            return;
        }
    }
    cout << "Member not found." << endl;
}

void Librarian::displayBooks() const {
    cout << "=== Library Books ===" << endl;
    if (books.size() == 0) {
        cout << "No books available." << endl;
        return;
    }
    for (int i = 0; i < books.size(); i++) {
        if (books[i] != nullptr) {
            cout << (i + 1) << ". ";
            books[i]->showData();
        }
    }
}

void Librarian::displayMembers() const {
    cout << "=== Library Members ===" << endl;
    if (members.size() == 0) {
        cout << "No members registered." << endl;
        return;
    }
    for (int i = 0; i < members.size(); i++) {
        if (members[i] != nullptr) {
            members[i]->displayInfo();
        }
    }
}

string Librarian::getEmployeeId() const {
    return employeeId;
}

void Librarian::setEmployeeId(const string &newEmployeeId) {
    employeeId = newEmployeeId;
}

void Librarian::displayInfo() const {
    cout << "[Librarian Profile] ID: " << getId() << " | Name: " << getName() << " | Employee ID: " << employeeId << endl;
}

void Librarian::displayStatistics() const {
    int totalTitles = books.size();
    int totalCopies = 0;
    for (int i = 0; i < books.size(); i++) {
        if (books[i] != nullptr) {
            totalCopies += books[i]->getCount();
        }
    }

    int totalMembers = members.size();
    int totalBorrowed = 0;
    for (int i = 0; i < members.size(); i++) {
        if (members[i] != nullptr) {
            totalBorrowed += members[i]->Borrowed;
        }
    }

    cout << "=== Library Statistics ===" << endl;
    cout << "Total Book Titles     : " << totalTitles << endl;
    cout << "Total Available Copies: " << totalCopies << endl;
    cout << "Total Borrowed Books  : " << totalBorrowed << endl;
    cout << "Total Active Members  : " << totalMembers << endl;
}

