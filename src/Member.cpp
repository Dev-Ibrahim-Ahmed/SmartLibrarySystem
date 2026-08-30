#include "../include/Member.h"
#include <iomanip>

Member::Member() : Person(), limit(3) , Borrowed(0){
    books = resizableArray<Book *>(3);
}

Member::Member(int id, const string &name, const string &password, int limit)
    : Person(id, name, password), limit(limit) , Borrowed(0){
    books = resizableArray<Book *>(3);
}

bool Member::canBorrow() const {
    return Borrowed < limit;
}

bool Member::borrowBook(resizableArray<Book> &catalog, size_t catalogSize, string query) {
    if (!canBorrow()) {
        cout << "  [Error] " << name << " reached the borrow limit of " << limit << " books. Cannot borrow \"" << query << "\"." << endl;
        return false;
    }

    resizableArray<Book *>found = BookFind(catalog, catalogSize, query);
    if (found.size() != 0) {
        if (found.size() == 1) {
            cout << "Found " << found.size() << "Book that satisfies your query !" << endl;
            cout << "Do you want to borrow it ? Y\\N" << endl;
            char ch; cin >> ch;
            if (ch == 'Y') {
                cout << "  [Success] " << name << " borrowed: \"" << found[found.size() - 1]->getTitle() << "\"" << endl;
                --*found[found.size() - 1];
                books[Borrowed] = found[found.size() - 1];
                Borrowed++;
            }
        }
        else {
            cout << "Found " << found.size() << "Books that satisfies your query !" << endl;
            for (int i = 0; i < found.size(); ++i) {
                cout << "[" << i + 1 << "]" << endl;
                found[i]->showData();
                cout << "----------------------------------------" << endl;
            }
            cout << "Which one would like to borrow ? (0 if none)" << endl;
            int idx; cin >> idx;
            if (idx) {
                cout << "  [Success] " << name << " borrowed: \"" << found[idx - 1]->getTitle() << "\"" << endl;
                --*found[idx - 1];
                books[Borrowed] = found[idx - 1];
                Borrowed++;
            }
        }
        return true;
    }

    cout << "  [Error] Book not found in catalog: \"" << query << "\"" << endl;
    return false;
}

bool Member::returnBook(const string &titleOrISBN) {
    for (size_t i = 0; i < Borrowed; ++i) {
        if (books[i]->getTitle() == titleOrISBN || books[i]->getISBN() == titleOrISBN) {
            cout << "  [Success] " << name << " returned: \"" << books[i]->getTitle() << "\"" << endl;
            books[i] = nullptr;
            Borrowed--;
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
    cout << "  Borrowed : " << Borrowed << " / " << limit << " books" << endl;
    if (Borrowed == 0) {
        cout << "  Books    : (none)" << endl;
    } else {
        cout << "  Books    :" << endl;
        for (size_t i = 0; i < Borrowed; ++i) {
            cout << "    [" << (i + 1) << "] " << books[i]->getTitle() << endl;
        }
    }
    cout << "----------------------------------------" << endl;
}

const resizableArray<Book *> Member::getBooks() const { return books; }
int Member::getLimit() const { return limit; }
void Member::setLimit(int newLimit) { limit = newLimit; }
