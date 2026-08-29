#include "Member.h"
#include <iomanip>

Member::Member() : Person(), limit(3) {}

Member::Member(int id, const string &name, const string &password, int limit)
    : Person(id, name, password), limit(limit) {}

bool Member::canBorrow() const {
    return (int)books.size() < limit;
}

bool Member::borrowBook(Book *catalog, size_t catalogSize, string query) {
    if (!canBorrow()) {
        cout << "  [Error] " << name << " reached the borrow limit of " << limit << " books. Cannot borrow \"" << query << "\"." << endl;
        return false;
    }

    Book *found = BookFind(catalog, catalogSize, query);
    if (found != nullptr) {
        books.push_back(found->getTitle());
        cout << "  [Success] " << name << " borrowed: \"" << found->getTitle() << "\"" << endl;
        delete[] found;
        return true;
    } else {
        cout << "  [Error] Book not found in catalog: \"" << query << "\"" << endl;
        return false;
    }
}

bool Member::returnBook(const string &titleOrISBN) {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i] == titleOrISBN) {
            cout << "  [Success] " << name << " returned: \"" << books[i] << "\"" << endl;
            books.erase(books.begin() + i);
            return true;
        }
    }
    cout << "  [Error] \"" << titleOrISBN << "\" was not found in " << name << "'s borrowed list." << endl;
    return false;
}

double Member::calculateFine(int daysLate, double ratePerDay) const {
    if (daysLate <= 0) return 0.0;
    return daysLate * ratePerDay;
}

void Member::displayInfo() const {
    cout << "----------------------------------------" << endl;
    cout << "  [Member Profile]" << endl;
    cout << "  ID       : " << id << endl;
    cout << "  Name     : " << name << endl;
    cout << "  Borrowed : " << books.size() << " / " << limit << " books" << endl;
    if (books.empty()) {
        cout << "  Books    : (none)" << endl;
    } else {
        cout << "  Books    :" << endl;
        for (size_t i = 0; i < books.size(); ++i) {
            cout << "    [" << (i + 1) << "] " << books[i] << endl;
        }
    }
    cout << "----------------------------------------" << endl;
}

const vector<string>& Member::getBooks() const { return books; }
int Member::getLimit() const { return limit; }
void Member::setLimit(int newLimit) { limit = newLimit; }
