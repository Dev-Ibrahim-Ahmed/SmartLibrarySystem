#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "Person.h"
#include "Book.h"
#include "Member.h"
#include "resizableArray.h"
#include <iostream>
#include <string>

using namespace std;

class Librarian : public Person {
    string employeeId;

public:
    Librarian();
    Librarian(int id, const string &name, const string &password, const string &employeeId);

    void addBook(resizableArray<Book>& catalog);
    void removeBook(resizableArray<Book>& catalog, const string& isbn);

    void addMember(resizableArray<Person *>& users);
    void removeMember(resizableArray<Person *>& users, int memberId);

    void displayBooks(const resizableArray<Book>& catalog) const;
    void displayMembers(const resizableArray<Person*>& users) const;

    string getType() const override { return "Librarian"; }
    string getEmployeeId() const;
    void setEmployeeId(const string &newEmployeeId);

    void menu() override;
    void displayInfo() const override;
    void displayStatistics() const;
};

#endif
