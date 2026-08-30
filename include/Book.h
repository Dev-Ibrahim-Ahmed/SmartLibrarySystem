#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

using namespace std;

class Book {
    string title, category, ISBN, author;
    int cnt;

public:
    Book();

    Book(const string &title, const string &ISBN, const string &category, const string &author, int cnt = 1);

    string getCategory() const { return category; }
    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    string getISBN() const { return ISBN; }
    int getCount() const { return cnt; }

    void showData() const {
        cout << title << " | Author: " << author << " | ISBN: " << ISBN << " | Category: " << category << " | Copies: "
                << cnt << endl;
    }

    bool operator==(const Book &x) const;

    bool operator>(const Book &x) const;

    void operator--();

    void operator++();

    friend istream &operator>>(istream &input, Book &x);

    ~Book();
};

#endif
