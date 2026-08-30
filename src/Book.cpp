//
// Created by Ibrahim on 8/28/2026.
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

void Book::operator --() {cnt--;}
void Book::operator ++() {cnt++;}

istream &operator >> (istream &input , Book &x) {
    std::cout << "Enter the title of the book : ";
    std::cin >> x.title;
    std::cout << "Enter the ISBN of the book : ";
    std::cin >> x.ISBN;
    std::cout << "Enter the category of the book : ";
    std::cin >> x.category;
    std::cout << "Enter the author of the book : ";
    std::cin >> x.author;
    return input;
}

Book::~Book() = default;