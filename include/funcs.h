#ifndef FUNCS_H
#define FUNCS_H

#include "Book.h"
#include "resizableArray.h"
#include <string>
#include <cstddef>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

resizableArray<Book*> BookFind(resizableArray<Book> &arr, const string &query);
Book* BookFind(resizableArray<Book> &arr, const Book &query);


template <class T>
T validateInput() {
    T val;
    if (!(cin >> val)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Invalid data type.");
    }

    char nextChar;
    if (cin.get(nextChar) && nextChar != '\n') {
        cin.unget();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Invalid characters found on input line.");
    }
    return val;
}

template <>
inline string validateInput<string>() {
    string val;
    getline(cin >> ws, val);
    if (val.empty()) {
        throw invalid_argument("Input cannot be empty.");
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
        catch (const invalid_argument &e) {
            cout << "  [Error] " << e.what() << " Please try again.\n";
        }
        catch (const runtime_error &e) {
            cout << "  [Fatal Error] " << e.what() << "\n";
            throw;
        }
    }
}

void sortBooksByTitle(resizableArray<Book> &arr);
void sortBooksByISBN(resizableArray<Book> &arr);
void sortBooksByTitle(resizableArray<Book*> &arr);

#endif