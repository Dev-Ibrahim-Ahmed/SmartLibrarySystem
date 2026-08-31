#include "DataManager.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void DataManager::loadBooks(const string &filePath, resizableArray<Book> &catalog) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Could not open " << filePath << endl;
        return;
    }

    json j;
    file >> j;

    for (int i = 0; i < (int)j.size(); i++) {
        string title = j[i]["title"];
        string author = j[i]["author"];
        string ISBN = j[i]["ISBN"];
        string category = j[i]["category"];
        int cnt = j[i]["cnt"];
        catalog.addItem(Book(title, ISBN, category, author, cnt));
    }
    cout << "Loaded " << catalog.size() << " books from database"<< endl;
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

    ofstream file(filePath);
    if (file.is_open()) {
        file << j.dump(4) << endl;
        cout << "Saved " << catalog.size() << " books to " << filePath << endl;
    }
}

void DataManager::loadPersons(const string &filePath, resizableArray<Person *> &users, const resizableArray<Book> &catalog) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Could not open " << filePath << endl;
        return;
    }

    json j;
    file >> j;

    for (int i = 0; i < (int)j.size(); i++) {
        string type = j[i]["type"];
        int id = j[i]["id"];
        string name = j[i]["name"];
        string password = j[i]["password"];

        if (type == "Librarian") {
            string empId = j[i]["employeeId"];
            users.addItem(new Librarian(id, name, password, empId));
        }
        else {
            int limit = j[i]["limit"];
            Member *m = new Member(id, name, password, limit);

            json bList = j[i]["borrowedBooks"];
            for (int k = 0; k < (int)bList.size(); k++) {
                string bookTitle = bList[k];
                for (int b = 0; b < catalog.size(); b++) {
                    if (catalog[b].getTitle() == bookTitle || catalog[b].getISBN() == bookTitle) {
                        if (m->Borrowed < m->limit) {
                            m->books.addItem(&catalog[b]);
                            m->Borrowed++;
                        }
                        break;
                    }
                }
            }
            users.addItem(m);
        }
    }
    cout << "Loaded " << users.size() << " users from database" << endl;
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
        }
        else {
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

    ofstream file(filePath);
    if (file.is_open()) {
        file << j.dump(4) << endl;
        cout << "Saved users to " << filePath << endl;
    }
}
