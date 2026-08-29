#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

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

    void setId(int newId);
    void setName(const string &newName);
    void setPassword(const string &newPassword);

    bool checkPassword(const string &pass) const;
    void displayInfo() const;
};

#endif // PERSON_H
