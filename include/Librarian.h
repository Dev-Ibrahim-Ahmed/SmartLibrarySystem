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

    void addBook(resizableArray<Book>& books);
    void removeBook(resizableArray<Book>& books);

    void addMember(resizableArray<Person *>& members);
    void removeMember(resizableArray<Person *>& members);

    void displayBooks(const resizableArray<Book*>& books) const;
    void displayMembers(const resizableArray<Member*>& members) const;

    string getType() const override{return "librarian";}
    string getEmployeeId() const;
    void setEmployeeId(const string &newEmployeeId);

    void menu() override;
    void displayInfo() const override;
    void displayStatistics() const;
};

#endif
