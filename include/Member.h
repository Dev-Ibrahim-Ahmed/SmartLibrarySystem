#ifndef MEMBER_H
#define MEMBER_H

#include "Person.h"
#include "Book.h"
#include "funcs.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Member : public Person {
public:
    vector<string> books;
    int limit;

    Member();
    Member(int id, const string &name, const string &password, int limit = 3);

    bool canBorrow() const;
    bool borrowBook(Book *catalog, size_t catalogSize, string query);
    bool returnBook(const string &titleOrISBN);
    double calculateFine(int daysLate, double ratePerDay) const;
    void displayInfo() const;

    const vector<string> &getBooks() const;
    int getLimit() const;
    void setLimit(int newLimit);
};

#endif // MEMBER_H
