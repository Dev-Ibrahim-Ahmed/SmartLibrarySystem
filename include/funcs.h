//
// Created by Ibrahim on 8/28/2026.
//

#ifndef SMARTLIBRARYSYSTEM_FUNCS_H
#define SMARTLIBRARYSYSTEM_FUNCS_H
#include "Book.h"
#include"resizableArray.h"


resizableArray<Book *>BookFind(const resizableArray<Book>&, size_t &,string &);
Book *BookFind(const resizableArray<Book>&, size_t &,Book &);


#endif //SMARTLIBRARYSYSTEM_FUNCS_H