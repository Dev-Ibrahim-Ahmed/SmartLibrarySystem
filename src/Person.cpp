#include "../include/Person.h"

Person::Person() : id(0), name(""), password("") {}
Person::Person(int id, const string &name, const string &password) : id(id), name(name), password(password) {}

int Person::getId() const { return id; }
string Person::getName() const { return name; }
string Person::getPassword() const { return password; }

void Person::setId(int newId) { id = newId; }
void Person::setName(const string &newName) { name = newName; }
void Person::setPassword(const string &newPassword) { password = newPassword; }

bool Person::checkPassword(const string &pass) const { return password == pass; }

void Person::displayInfo() const {
    cout << "----------------------------------------" << endl;
    cout << "  [Person Profile]" << endl;
    cout << "  ID   : " << id << endl;
    cout << "  Name : " << name << endl;
    cout << "----------------------------------------" << endl;
}
