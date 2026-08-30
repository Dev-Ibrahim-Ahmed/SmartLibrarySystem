//
// Created by Ibrahim on 8/28/2026.
//

#ifndef SMARTLIBRARYSYSTEM_FUNCS_H
#define SMARTLIBRARYSYSTEM_FUNCS_H
#include <iostream>
#include "Book.h"
#include"resizableArray.h"
#include<limits>
using std::cin;
using std::cout;
using std::endl;

resizableArray<Book *>BookFind(resizableArray<Book>&,const string &);
Book *BookFind(resizableArray<Book>&, const Book &);
template <class T>
T validateInput() {
    T val;
    if (!(cin >> val)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid data type.");
    }

    char nextChar;
    if (cin.get(nextChar) && nextChar != '\n') {
        cin.unget();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid characters found on input line.");
    }
    return val;
}

template <class T>
void validate(T &x, const string &prompt = "Enter value : ") {
    while (true) {
        try {
            cout << prompt;
            x = validateInput<T>();
            break;
        }
        catch (const std::invalid_argument &e) {
            cout << "  [Error] " << e.what() << " Please try again.\n";
        }
        catch (const std::runtime_error &e) {
            cout << "  [Fatal Error] " << e.what() << "\n";
            throw;
        }
    }
}
#endif //SMARTLIBRARYSYSTEM_FUNCS_H