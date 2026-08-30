#ifndef FUNCS_H
#define FUNCS_H

#include "Book.h"
#include "resizableArray.h"
#include <string>
#include <cstddef>

using namespace std;

resizableArray<Book*> BookFind(const resizableArray<Book> &arr, const size_t &n, const string &query);
Book* BookFind(const resizableArray<Book> &arr, const size_t &n, const Book &query);

void sortBooksByTitle(resizableArray<Book> &arr);
void sortBooksByISBN(resizableArray<Book> &arr);
void sortBooksByTitle(resizableArray<Book*> &arr);

#endif