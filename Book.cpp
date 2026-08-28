//
// Created by compi_tech on 8/28/2026.
//

#include "Book.h"

Book::Book(string &title , string &ISBN , string &category , string &author) {
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