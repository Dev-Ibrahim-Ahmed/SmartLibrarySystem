#include "DataManager.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

static bool openInputFile(const string &filePath, ifstream &file) {
    file.open(filePath);
    if (file.is_open()) return true;

    // Fallback if launched from different working directory
    string alt = (filePath.rfind("../", 0) == 0) ? filePath.substr(3) : ("../" + filePath);
    file.open(alt);
    return file.is_open();
}

static bool openOutputFile(const string &filePath, ofstream &file, string &actualPath) {
    file.open(filePath);
    if (file.is_open()) {
        actualPath = filePath;
        return true;
    }

    string alt = (filePath.rfind("../", 0) == 0) ? filePath.substr(3) : ("../" + filePath);
    file.open(alt);
    if (file.is_open()) {
        actualPath = alt;
        return true;
    }
    return false;
}

void DataManager::loadBooks(const string &filePath, resizableArray<Book> &catalog) {
    ifstream file;
    if (!openInputFile(filePath, file)) {
        cout << "Could not open " << filePath << endl;
        return;
    }

    json j;
    try {
        file >> j;
    } catch (...) {
        cout << "Error reading JSON from " << filePath << endl;
        return;
    }

    for (int i = 0; i < (int)j.size(); i++) {
        string title = j[i].value("title", "");
        string author = j[i].value("author", "");
        string ISBN = j[i].value("ISBN", "");
        string category = j[i].value("category", "");
        int cnt = j[i].value("cnt", 1);
        catalog.addItem(Book(title, ISBN, category, author, cnt));
    }
    cout << "Loaded " << catalog.size() << " books from database." << endl;
}

void DataManager::saveBooks(const string &filePath, const resizableArray<Book> &catalog) {
    json j = json::array();
    for (int i = 0; i < catalog.size(); i++) {
        json b;
        b["title"] = catalog[i].getTitle();
        b["author"] = catalog[i].getAuthor();
        b["ISBN"] = catalog[i].getISBN();
        b["category"] = catalog[i].getCategory();
        b["cnt"] = catalog[i].getCount();
        j.push_back(b);
    }

    ofstream file;
    string actualPath;
    if (openOutputFile(filePath, file, actualPath)) {
        file << j.dump(4) << endl;
        cout << "Saved " << catalog.size() << " books to " << actualPath << endl;
    }
}

void DataManager::loadPersons(const string &filePath, resizableArray<Person *> &users, const resizableArray<Book> &catalog) {
    ifstream file;
    if (!openInputFile(filePath, file)) {
        cout << "Could not open " << filePath << endl;
        return;
    }

    json j;
    try {
        file >> j;
    } catch (...) {
        cout << "Error reading JSON from " << filePath << endl;
        return;
    }

    for (int i = 0; i < (int)j.size(); i++) {
        string type = j[i].value("type", "Member");
        int id = j[i].value("id", 0);
        string name = j[i].value("name", "");
        string password = j[i].value("password", "");

        if (type == "Librarian") {
            string empId = j[i].value("employeeId", "");
            users.addItem(new Librarian(id, name, password, empId));
        } else {
            int limit = j[i].value("limit", 3);
            Member *m = new Member(id, name, password, limit);

            if (j[i].contains("borrowedBooks") && j[i]["borrowedBooks"].is_array()) {
                json bList = j[i]["borrowedBooks"];
                for (int k = 0; k < (int)bList.size(); k++) {
                    string bookTitle = bList[k];
                    for (int b = 0; b < catalog.size(); b++) {
                        if (catalog[b].getTitle() == bookTitle || catalog[b].getISBN() == bookTitle) {
                            if (m->Borrowed < m->limit) {
                                m->books.addItem(const_cast<Book*>(&catalog[b]));
                                m->Borrowed++;
                            }
                            break;
                        }
                    }
                }
            }
            users.addItem(m);
        }
    }
    cout << "Loaded " << users.size() << " users from database." << endl;
}

void DataManager::savePersons(const string &filePath, const resizableArray<Person *> &users) {
    json j = json::array();
    for (int i = 0; i < users.size(); i++) {
        if (users[i] == nullptr) continue;

        Member *m = dynamic_cast<Member*>(users[i]);
        if (m != nullptr) {
            json bList = json::array();
            for (int k = 0; k < m->Borrowed; k++) {
                if (m->books[k] != nullptr) {
                    bList.push_back(m->books[k]->getTitle());
                }
            }

            json u;
            u["type"] = "Member";
            u["id"] = m->getId();
            u["name"] = m->getName();
            u["password"] = m->getPassword();
            u["limit"] = m->getLimit();
            u["borrowedBooks"] = bList;
            j.push_back(u);
        } else {
            Librarian *lib = dynamic_cast<Librarian*>(users[i]);
            if (lib != nullptr) {
                json u;
                u["type"] = "Librarian";
                u["id"] = lib->getId();
                u["name"] = lib->getName();
                u["password"] = lib->getPassword();
                u["employeeId"] = lib->getEmployeeId();
                j.push_back(u);
            }
        }
    }

    ofstream file;
    string actualPath;
    if (openOutputFile(filePath, file, actualPath)) {
        file << j.dump(4) << endl;
        cout << "Saved users to " << actualPath << endl;
    }
}