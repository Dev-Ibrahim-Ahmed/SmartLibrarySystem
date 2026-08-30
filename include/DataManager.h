#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "Book.h"
#include "Person.h"
#include "Member.h"
#include "Librarian.h"
#include "resizableArray.h"
#include <string>

using namespace std;

class DataManager {
public:
    static void loadBooks(const string &filePath, resizableArray<Book> &catalog);
    static void saveBooks(const string &filePath, const resizableArray<Book> &catalog);
    static void loadPersons(const string &filePath, resizableArray<Person*> &users, const resizableArray<Book> &catalog);
    static void savePersons(const string &filePath, const resizableArray<Person*> &users);
};

#endif
