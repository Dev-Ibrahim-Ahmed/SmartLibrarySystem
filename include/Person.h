#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

#include "Book.h"

using namespace std;

class Person {
protected:
    int id;
    string name;
    string password;

public:
    Person();
    Person(int id, const string &name, const string &password);
    virtual ~Person() = default;

    int getId() const;
    string getName() const;
    string getPassword() const;
    virtual int getLimit() const = 0;
    virtual int getBorrowed() const = 0;
    void setId(int newId);
    void setName(const string &newName);
    void setPassword(const string &newPassword);
    bool checkPassword(const string &pass) const;
    virtual void menu() = 0;
    virtual string getType() const = 0;
    virtual void displayInfo() const = 0;
    virtual Book *operator [](int i) const = 0;
};

#endif
