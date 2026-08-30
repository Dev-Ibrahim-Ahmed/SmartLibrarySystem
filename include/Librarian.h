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
public:
    resizableArray<Book*> books;
    resizableArray<Member*> members;
    string employeeId;

    Librarian();
    Librarian(int id, const string &name, const string &password, const string &employeeId);

    void addBook(Book* book);
    void removeBook(Book* book);

    void addMember(Member* member);
    void removeMember(Member* member);

    void displayBooks() const;
    void displayMembers() const;

    string getEmployeeId() const;
    void setEmployeeId(const string &newEmployeeId);

    void displayInfo() const override;
    void displayStatistics() const;
};

#endif
