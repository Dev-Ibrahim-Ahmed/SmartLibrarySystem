//
// Created by compi_tech on 8/28/2026.
//

#ifndef SMARTLIBRARYSYSTEM_BOOK_H
#define SMARTLIBRARYSYSTEM_BOOK_H
#include <string>
using std::string;


class Book {
    string title , category , ISBN , author;
    int cnt;
public :
    Book(const string &,const string &,const string &,const string & ,const int &);
    Book() {title = category = author = ISBN = ""; cnt = 0;};
    [[nodiscard]] string getCategory() const{return category;}
    [[nodiscard]] string getAuthor()const{return author;}
    [[nodiscard]] string getTitle()const{return title;}
    [[nodiscard]] string getISBN()const{return ISBN;}
    friend Book *BookFind(Book *, size_t ,string &);
    friend Book *BookFind(Book *, size_t ,Book &);
    bool operator == (const Book &x) const;
    bool operator > (const Book&x)const;
    ~Book();
};


#endif //SMARTLIBRARYSYSTEM_BOOK_H