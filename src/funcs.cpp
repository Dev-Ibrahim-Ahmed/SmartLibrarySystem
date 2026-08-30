//
// Created by Ibrahim on 8/28/2026.
//

#include "../include/funcs.h"

resizableArray<Book *> BookFind(const resizableArray<Book> &arr ,const size_t &n,const string &query) {
    resizableArray<Book *> x;
    for (int i = 0; i < n; ++i) {
        if (arr[i].getAuthor() == query || arr[i].getCategory() == query ||
            arr[i].getISBN() == query || arr[i].getTitle() == query)x.addItem(&arr[i]);
    }
    return x;
}

Book *BookFind(const resizableArray<Book> &arr ,const size_t &n,const Book &query) {
    int l = 0 , r = n , mid , ans = -1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (arr[mid].getISBN() < query.getISBN())r = mid - 1;
        else if (arr[mid].getISBN() > query.getISBN())l = mid + 1;
        else ans = mid;
    }
    if (ans == -1)return nullptr;
    return &arr[ans];
}


