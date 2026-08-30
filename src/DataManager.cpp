#include "DataManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

void DataManager::createDefaultBooksFile(const string &) {}
void DataManager::createDefaultPersonsFile(const string &) {}

void DataManager::loadBooks(const string &filePath, resizableArray<Book> &catalog) {
    ifstream file(filePath);
    if (!file.is_open()) {
        catalog.addItem(Book("The Great Gatsby", "978-0743273565", "Classic", "F. Scott Fitzgerald", 3));
        catalog.addItem(Book("1984", "978-0451524935", "Dystopian", "George Orwell", 2));
        catalog.addItem(Book("To Kill a Mockingbird", "978-0061120084", "Classic", "Harper Lee", 4));
        catalog.addItem(Book("The Alchemist", "978-0062315007", "Adventure", "Paulo Coelho", 5));
        catalog.addItem(Book("Clean Code", "978-0132350884", "Software Engineering", "Robert C. Martin", 3));
        return;
    }

    string line;
    string title, author, ISBN, category;
    int cnt = 1;

    while (getline(file, line)) {
        size_t tPos = line.find("\"title\":");
        if (tPos != string::npos) {
            size_t s = line.find('"', tPos + 8) + 1;
            size_t e = line.find('"', s);
            title = line.substr(s, e - s);
        }
        size_t aPos = line.find("\"author\":");
        if (aPos != string::npos) {
            size_t s = line.find('"', aPos + 9) + 1;
            size_t e = line.find('"', s);
            author = line.substr(s, e - s);
        }
        size_t iPos = line.find("\"ISBN\":");
        if (iPos != string::npos) {
            size_t s = line.find('"', iPos + 7) + 1;
            size_t e = line.find('"', s);
            ISBN = line.substr(s, e - s);
        }
        size_t cPos = line.find("\"category\":");
        if (cPos != string::npos) {
            size_t s = line.find('"', cPos + 11) + 1;
            size_t e = line.find('"', s);
            category = line.substr(s, e - s);
        }
        size_t cntPos = line.find("\"cnt\":");
        if (cntPos != string::npos) {
            size_t s = cntPos + 6;
            while (s < line.size() && (line[s] == ' ' || line[s] == ':')) s++;
            cnt = atoi(line.substr(s).c_str());
            if (!title.empty() && !ISBN.empty()) {
                catalog.addItem(Book(title, ISBN, category, author, cnt));
                title = author = ISBN = category = "";
                cnt = 1;
            }
        }
    }
    if (catalog.size() == 0) {
        catalog.addItem(Book("The Great Gatsby", "978-0743273565", "Classic", "F. Scott Fitzgerald", 3));
        catalog.addItem(Book("1984", "978-0451524935", "Dystopian", "George Orwell", 2));
        catalog.addItem(Book("To Kill a Mockingbird", "978-0061120084", "Classic", "Harper Lee", 4));
        catalog.addItem(Book("The Alchemist", "978-0062315007", "Adventure", "Paulo Coelho", 5));
        catalog.addItem(Book("Clean Code", "978-0132350884", "Software Engineering", "Robert C. Martin", 3));
    }
    cout << "Loaded " << catalog.size() << " books." << endl;
}

void DataManager::saveBooks(const string &filePath, const resizableArray<Book> &catalog) {
    ofstream file(filePath);
    if (!file.is_open()) return;
    file << "[\n";
    for (int i = 0; i < catalog.size(); i++) {
        file << "  {\n";
        file << "    \"title\": \"" << catalog[i].getTitle() << "\",\n";
        file << "    \"author\": \"" << catalog[i].getAuthor() << "\",\n";
        file << "    \"ISBN\": \"" << catalog[i].getISBN() << "\",\n";
        file << "    \"category\": \"" << catalog[i].getCategory() << "\",\n";
        file << "    \"cnt\": " << catalog[i].getCount() << "\n";
        file << "  }" << (i + 1 < catalog.size() ? ",\n" : "\n");
    }
    file << "]\n";
}

void DataManager::saveBooks(const string &filePath, const resizableArray<Book *> &books) {
    ofstream file(filePath);
    if (!file.is_open()) return;
    file << "[\n";
    for (int i = 0; i < books.size(); i++) {
        if (books[i] == nullptr) continue;
        file << "  {\n";
        file << "    \"title\": \"" << books[i]->getTitle() << "\",\n";
        file << "    \"author\": \"" << books[i]->getAuthor() << "\",\n";
        file << "    \"ISBN\": \"" << books[i]->getISBN() << "\",\n";
        file << "    \"category\": \"" << books[i]->getCategory() << "\",\n";
        file << "    \"cnt\": " << books[i]->getCount() << "\n";
        file << "  }" << (i + 1 < books.size() ? ",\n" : "\n");
    }
    file << "]\n";
}

void DataManager::loadPersons(const string &filePath, resizableArray<Person *> &users, const resizableArray<Book> &) {
    ifstream file(filePath);
    if (!file.is_open()) {
        users.addItem(new Librarian(1, "Ibrahim Al Abd", "admin123", "LIB-001"));
        users.addItem(new Librarian(2, "Dr. Mona Tarek", "pass2026", "LIB-002"));
        users.addItem(new Member(101, "Ahmed Abdoo", "1234", 3));
        users.addItem(new Member(102, "Sondos Ahmed", "pass2026", 3));
        users.addItem(new Member(103, "Omar Khaled", "9012", 3));
        users.addItem(new Member(104, "Sara Hassan", "5678", 3));
        cout << "Loaded " << users.size() << " default users." << endl;
        return;
    }

    string line;
    string type, name, password, empId;
    int id = 0, limit = 3;

    while (getline(file, line)) {
        size_t tyPos = line.find("\"type\":");
        if (tyPos != string::npos) {
            size_t s = line.find('"', tyPos + 7) + 1;
            size_t e = line.find('"', s);
            type = line.substr(s, e - s);
        }
        size_t idPos = line.find("\"id\":");
        if (idPos != string::npos) {
            size_t s = idPos + 5;
            while (s < line.size() && (line[s] == ' ' || line[s] == ':')) s++;
            id = atoi(line.substr(s).c_str());
        }
        size_t nPos = line.find("\"name\":");
        if (nPos != string::npos) {
            size_t s = line.find('"', nPos + 7) + 1;
            size_t e = line.find('"', s);
            name = line.substr(s, e - s);
        }
        size_t pPos = line.find("\"password\":");
        if (pPos != string::npos) {
            size_t s = line.find('"', pPos + 11) + 1;
            size_t e = line.find('"', s);
            password = line.substr(s, e - s);
        }
        size_t ePos = line.find("\"employeeId\":");
        if (ePos != string::npos) {
            size_t s = line.find('"', ePos + 13) + 1;
            size_t e = line.find('"', s);
            empId = line.substr(s, e - s);
        }
        size_t limPos = line.find("\"limit\":");
        if (limPos != string::npos) {
            size_t s = limPos + 8;
            while (s < line.size() && (line[s] == ' ' || line[s] == ':')) s++;
            limit = atoi(line.substr(s).c_str());
        }

        if (line.find('}') != string::npos && id != 0) {
            if (type == "Librarian") {
                users.addItem(new Librarian(id, name, password, empId));
            } else {
                users.addItem(new Member(id, name, password, limit));
            }
            type = name = password = empId = "";
            id = 0;
            limit = 3;
        }
    }

    if (users.size() == 0) {
        users.addItem(new Librarian(1, "Ibrahim Al Abd", "admin123", "LIB-001"));
        users.addItem(new Librarian(2, "Dr. Mona Tarek", "pass2026", "LIB-002"));
        users.addItem(new Member(101, "Ahmed Abdoo", "1234", 3));
        users.addItem(new Member(102, "Sondos Ahmed", "pass2026", 3));
        users.addItem(new Member(103, "Omar Khaled", "9012", 3));
        users.addItem(new Member(104, "Sara Hassan", "5678", 3));
    }
    cout << "Loaded " << users.size() << " users." << endl;
}

void DataManager::savePersons(const string &filePath, const resizableArray<Person *> &users) {
    ofstream file(filePath);
    if (!file.is_open()) return;
    file << "[\n";
    for (int i = 0; i < users.size(); i++) {
        if (users[i] == nullptr) continue;
        Member *m = dynamic_cast<Member*>(users[i]);
        if (m != nullptr) {
            file << "  {\n";
            file << "    \"type\": \"Member\",\n";
            file << "    \"id\": " << m->getId() << ",\n";
            file << "    \"name\": \"" << m->getName() << "\",\n";
            file << "    \"password\": \"" << m->getPassword() << "\",\n";
            file << "    \"limit\": " << m->getLimit() << "\n";
            file << "  }" << (i + 1 < users.size() ? ",\n" : "\n");
        } else {
            Librarian *lib = dynamic_cast<Librarian*>(users[i]);
            if (lib != nullptr) {
                file << "  {\n";
                file << "    \"type\": \"Librarian\",\n";
                file << "    \"id\": " << lib->getId() << ",\n";
                file << "    \"name\": \"" << lib->getName() << "\",\n";
                file << "    \"password\": \"" << lib->getPassword() << "\",\n";
                file << "    \"employeeId\": \"" << lib->getEmployeeId() << "\"\n";
                file << "  }" << (i + 1 < users.size() ? ",\n" : "\n");
            }
        }
    }
    file << "]\n";
}
