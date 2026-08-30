//
// Created by Ibrahim on 8/28/2026.
//

#ifndef SMARTLIBRARYSYSTEM_BOOK_H
#define SMARTLIBRARYSYSTEM_BOOK_H
#include <iostream>
#include <string>
using std::string;
using std::istream;
using std::ostream;

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
    void showData() const{
        std::cout << "Title : " << title << std::endl;
        std::cout << "ISBN : " << ISBN << std::endl;
        std::cout << "Category : " << category << std::endl;
        std::cout << "Author : " << author << std::endl;
        std::cout << "Number of Copies : " << cnt << std::endl;
    }
    bool operator == (const Book &x) const;
    bool operator > (const Book&x)const;
    void operator --();
    void operator ++();
    friend istream &operator >> (istream &input , Book &x);
    ~Book();
};


#endif //SMARTLIBRARYSYSTEM_BOOK_H