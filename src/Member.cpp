#include "Member.h"
#include "funcs.h"
#include <iostream>

Member::Member() : Person(), limit(3), Borrowed(0) {
    books = resizableArray<Book*>(limit);
}

Member::Member(int id, const string &name, const string &password, int limit)
    : Person(id, name, password), limit(limit), Borrowed(0) {
    books = resizableArray<Book*>(limit);
}

bool Member::canBorrow() const {
    return Borrowed < limit;
}

void Member::borrowBook(resizableArray<Book> &catalog , string query) {
    if (!canBorrow()) {
        cout << "Error: " << getName() << " reached the borrow limit of " << limit << " books." << endl;
        return;
    }

    resizableArray<Book*> found = BookFind(catalog , query);
    if (found.size() > 0) {
        if (found.size() == 1) {
            cout << "Found 1 book matching your query. Borrow it? (Y/N): ";
            char ch = '0';
            while (true) {
                validate(ch , "Enter your choice : ");
                if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n')cout << "Invalid choice";
                else break;
            }
            if (ch == 'Y' || ch == 'y') {
                if (found[0]->getCount()) {
                    Book* b = found[0];
                    cout << getName() << " borrowed: " << b->getTitle() << endl;
                    --(*b);
                    books[Borrowed++] = b;
                }
                else cout << "The Book isn't available" << endl;
                return;
            }
        } else {
            cout << "Found " << found.size() << " books matching your query:" << endl;
            for (int i = 0; i < found.size(); i++) {
                cout << "[" << (i + 1) << "] ";
                found[i]->showData();
            }
            cout << "Enter the number of the book to borrow (0 to cancel): ";
            int idx;
            while (true) {
                validate(idx , "Enter your choice : ");
                if (idx < 0 || idx > found.size())cout << "Invalid choice";
                else break;
            }
            if (idx > 0 && idx <= found.size()) {
                Book* b = found[idx - 1];
                cout << getName() << " borrowed: " << b->getTitle() << endl;
                --(*b);
                books[Borrowed++] = b;
            }
        }
        return;
    }

    cout << "Error: Book not found in catalog: " << query << endl;
}

void Member::returnBook(const string &titleOrISBN) {
    for (int i = 0; i < Borrowed; i++) {
        if (books[i] != nullptr && (books[i]->getTitle() == titleOrISBN || books[i]->getISBN() == titleOrISBN)) {
            cout << "How many days did you borrow this book for ?" << endl;
            int x = 0;
            while (true) {
                validate(x);
                if (x <= 0)cout << "Invalid number";
                else break;
            }
            calculateFine(x);
            cout << getName() << " returned: " << books[i]->getTitle() << endl;
            ++books[i];
            for (int j = i; j < Borrowed - 1; ++j) {
                books[j] = books[j + 1];
            }
            books[Borrowed - 1] = nullptr;
            Borrowed--;
            return;
        }
    }
    cout << "Error: " << titleOrISBN << " not found in borrowed list." << endl;
}

void Member::calculateFine(int daysLate, double ratePerDay)  {
    fines += daysLate * ratePerDay;
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


void Member::setLimit(int newLimit) {
    limit = newLimit;
}

