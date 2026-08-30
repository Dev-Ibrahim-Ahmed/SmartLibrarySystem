#include "Book.h"

Book::Book() : title(""), category(""), ISBN(""), author(""), cnt(0) {}

Book::Book(const string &title, const string &ISBN, const string &category, const string &author, int cnt)
    : title(title), category(category), ISBN(ISBN), author(author), cnt(cnt) {}

bool Book::operator==(const Book &x) const {
    return title == x.title || ISBN == x.ISBN || category == x.category || author == x.author;
}

bool Book::operator>(const Book &x) const {
    return ISBN > x.ISBN;
}

void Book::operator--() {
    if (cnt > 0) cnt--;
}

void Book::operator++() {
    cnt++;
}

istream& operator>>(istream &input, Book &x) {
    cout << "Enter title: ";
    input >> x.title;
    cout << "Enter ISBN: ";
    input >> x.ISBN;
    cout << "Enter category: ";
    input >> x.category;
    cout << "Enter author: ";
    input >> x.author;
    return input;
}

Book::~Book() = default;