//
// Created by compi_tech on 8/28/2026.
//

#include "../include/funcs.h"

Book* BookFind(const Book *arr ,const size_t &n,const string &query) {
    int cnt = 0;
    bool marked[n];
    for (int i = 0; i < n; ++i)marked[i] = false;
    for (int i = 0; i < n; ++i) {
        if (arr[i].getAuthor() == query || arr[i].getCategory() == query ||
            arr[i].getISBN() == query || arr[i].getTitle() == query)cnt++ , marked[i] = true;
    }

    Book* x = new Book[cnt];

    cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (marked[i])x[cnt] = arr[i];
    }
    return x;
}

Book* BookFind(Book *arr ,const size_t &n,const Book &query) {
    int l = 0 , r = n , mid , ans = -1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (arr[mid].getISBN() < query.getISBN())r = mid - 1;
        else if (arr[mid].getISBN() > query.getISBN())l = mid + 1;
        else ans = mid;
    }
    return (arr + ans);
}

template<typename Type>

void resize(Type *x , size_t &sz) {
    Type *y = new Type[2 * sz];
    for (int i = 0; i < sz; ++i) {
        y[i] == x[i];
    }
    delete[] x;
    x = y;
}