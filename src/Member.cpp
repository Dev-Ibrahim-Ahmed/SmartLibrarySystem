#include "Member.h"
#include <iostream>

Member::Member() : Person(), limit(3), Borrowed(0) {
    books = resizableArray<Book*>(3);
}

Member::Member(int id, const string &name, const string &password, int limit)
    : Person(id, name, password), limit(limit), Borrowed(0) {
    books = resizableArray<Book*>(3);
}

bool Member::canBorrow() const {
    return Borrowed < limit;
}

bool Member::borrowBook(resizableArray<Book> &catalog, size_t catalogSize, string query) {
    if (!canBorrow()) {
        cout << "Error: " << getName() << " reached the borrow limit of " << limit << " books." << endl;
        return false;
    }

    resizableArray<Book*> found = BookFind(catalog, catalogSize, query);
    if (found.size() > 0) {
        if (found.size() == 1) {
            cout << "Found 1 book matching your query. Borrow it? (Y/N): ";
            char ch;
            cin >> ch;
            if (ch == 'Y' || ch == 'y') {
                Book* b = found[0];
                cout << getName() << " borrowed: " << b->getTitle() << endl;
                --(*b);
                books[Borrowed++] = b;
            }
        } else {
            cout << "Found " << found.size() << " books matching your query:" << endl;
            for (int i = 0; i < found.size(); i++) {
                cout << "[" << (i + 1) << "] ";
                found[i]->showData();
            }
            cout << "Enter number to borrow (0 to cancel): ";
            int idx;
            cin >> idx;
            if (idx > 0 && idx <= found.size()) {
                Book* b = found[idx - 1];
                cout << getName() << " borrowed: " << b->getTitle() << endl;
                --(*b);
                books[Borrowed++] = b;
            }
        }
        return true;
    }

    cout << "Error: Book not found in catalog: " << query << endl;
    return false;
}

bool Member::returnBook(const string &titleOrISBN) {
    for (int i = 0; i < Borrowed; i++) {
        if (books[i] != nullptr && (books[i]->getTitle() == titleOrISBN || books[i]->getISBN() == titleOrISBN)) {
            cout << getName() << " returned: " << books[i]->getTitle() << endl;
            books[i] = nullptr;
            Borrowed--;
            return true;
        }
    }
    cout << "Error: " << titleOrISBN << " not found in borrowed list." << endl;
    return false;
}

double Member::calculateFine(int daysLate, double ratePerDay) const {
    if (daysLate <= 0) return 0.0;
    return daysLate * ratePerDay;
}

void Member::displayInfo() const {
    cout << "[Member Profile] ID: " << getId() << " | Name: " << getName() << " | Borrowed: " << Borrowed << "/" << limit << endl;
    if (Borrowed == 0) {
        cout << "  No borrowed books." << endl;
    } else {
        for (int i = 0; i < Borrowed; i++) {
            if (books[i] != nullptr) {
                cout << "  - " << books[i]->getTitle() << endl;
            }
        }
    }
}

const resizableArray<Book*>& Member::getBooks() const {
    return books;
}

int Member::getLimit() const {
    return limit;
}

void Member::setLimit(int newLimit) {
    limit = newLimit;
}
