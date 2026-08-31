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

void Member::borrowBook(resizableArray<Book> &catalog, string query) {
    if (!canBorrow()) {
        cout << "Error: " << getName() << " reached the borrow limit of " << limit << " books." << endl;
        return;
    }

    resizableArray<Book*> found = BookFind(catalog, query);
    if (found.size() > 0) {
        if (found.size() == 1) {
            cout << "Found 1 book matching your query (" << found[0]->getTitle() << "). Borrow it? (Y/N): ";
            char ch;
            while (true) {
                validate(ch, "Enter your choice: ");
                if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n') break;
                cout << "Invalid choice! ";
            }
            if (ch == 'Y' || ch == 'y') {
                if (found[0]->getCount() > 0) {
                    Book* b = found[0];
                    --(*b);
                    books.addItem(b);
                    Borrowed++;
                    cout << getName() << " successfully borrowed: " << b->getTitle() << endl;
                } else {
                    cout << "The book is currently out of stock." << endl;
                }
            }
            return;
        } else {
            cout << "Found " << found.size() << " books matching your query:" << endl;
            for (int i = 0; i < found.size(); i++) {
                cout << "[" << (i + 1) << "] ";
                found[i]->showData();
            }
            int idx = 0;
            while (true) {
                validate(idx, "Enter the number of the book to borrow (0 to cancel): ");
                if (idx >= 0 && idx <= found.size()) break;
                cout << "Invalid choice! ";
            }
            if (idx > 0) {
                Book* b = found[idx - 1];
                if (b->getCount() > 0) {
                    --(*b);
                    books.addItem(b);
                    Borrowed++;
                    cout << getName() << " successfully borrowed: " << b->getTitle() << endl;
                } else {
                    cout << "The book is currently out of stock." << endl;
                }
            }
            return;
        }
    }

    cout << "Error: No books found matching: " << query << endl;
}

void Member::returnBook(const string &titleOrISBN) {
    for (int i = 0; i < Borrowed; i++) {
        if (books[i] != nullptr && (books[i]->getTitle() == titleOrISBN || books[i]->getISBN() == titleOrISBN)) {
            int daysLate = 0;
            while (true) {
                validate(daysLate, "How many days late is this book? (0 if on time): ");
                if (daysLate >= 0) break;
                cout << "Invalid number! ";
            }
            if (daysLate > 0) {
                calculateFine(daysLate);
            }

            ++(*books[i]); // Increment stock back in catalog
            cout << getName() << " returned: " << books[i]->getTitle() << endl;

            books.removeItemAt(i);
            Borrowed--;
            return;
        }
    }
    cout << "Error: " << titleOrISBN << " not found in your borrowed list." << endl;
}

void Member::calculateFine(int daysLate, double ratePerDay) {
    double addedFine = daysLate * ratePerDay;
    fines += addedFine;
    cout << "Fine assessed: $" << addedFine << " (Total Fines: $" << fines << ")" << endl;
}

void Member::displayInfo() const {
    cout << "[Member Profile] ID: " << getId() << " | Name: " << getName()
         << " | Borrowed: " << Borrowed << "/" << limit
         << " | Fines Owed: $" << fines << endl;
    if (Borrowed == 0) {
        cout << "  No borrowed books." << endl;
    } else {
        for (int i = 0; i < Borrowed; i++) {
            if (books[i] != nullptr) {
                cout << "  " << (i + 1) << ". " << books[i]->getTitle() << " [ISBN: " << books[i]->getISBN() << "]" << endl;
            }
        }
    }
}

const resizableArray<Book*>& Member::getBooks() const { return books; }
void Member::setLimit(int newLimit) { limit = newLimit; }