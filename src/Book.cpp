//
// Created by compi_tech on 8/28/2026.
//

#include "../include/Book.h"

Book::Book(const string &title ,const string &ISBN ,const string &category ,const string &author , const int &cnt) {
    this->cnt = cnt;
    this->title = title;
    this->ISBN = ISBN;
    this->category = category;
    this->author = author;
}

bool Book::operator==(const Book &x) const {
    return title == x.title || ISBN == x.ISBN || category == x.category || author == x.author;
}

bool Book::operator>(const Book &x) const {
    return this->ISBN > x.getISBN();
}

Book::~Book() = default;