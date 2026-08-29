//
// Created by compi_tech on 8/28/2026.
//

#ifndef SMARTLIBRARYSYSTEM_FUNCS_H
#define SMARTLIBRARYSYSTEM_FUNCS_H
#include "Book.h"


Book *BookFind(Book *, size_t &,string &);
Book *BookFind(Book *, size_t &,Book &);
template<typename Type>
void resize(Type *, size_t &);

#endif //SMARTLIBRARYSYSTEM_FUNCS_H