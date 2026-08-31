#ifndef MEMBER_H
#define MEMBER_H

#include "Person.h"
#include "Book.h"
#include "funcs.h"
#include "resizableArray.h"
#include "menus.h"
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class Member : public Person {
    int fines = 0;
    int limit;
    int Borrowed;
    resizableArray<Book*> books;
public:

    Member();
    Member(int id, const string &name, const string &password, int limit = 3);

    bool canBorrow() const;
    void borrowBook(resizableArray<Book> &catalog , string query);
    void returnBook(const string &titleOrISBN);
    void calculateFine(int daysLate, double ratePerDay = 2) ;
    int getBorrowed()const override{return Borrowed;}
    string getType() const override{return "Member";}
    void displayInfo() const override;
    void menu() override;
    const resizableArray<Book*>& getBooks() const;
    int getLimit() const override{return limit;}
    void setLimit(int newLimit);
    Book * operator [](int i)const override{return books[i];}
};

#endif
