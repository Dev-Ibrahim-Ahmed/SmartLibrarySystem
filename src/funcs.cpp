#include "funcs.h"

resizableArray<Book*> BookFind(const resizableArray<Book> &arr, const size_t &n, const string &query) {
    resizableArray<Book*> x;
    for (size_t i = 0; i < n; i++) {
        if (arr[i].getAuthor() == query || arr[i].getCategory() == query ||
            arr[i].getISBN() == query || arr[i].getTitle() == query) {
            x.addItem(const_cast<Book*>(&arr[i]));
        }
    }
    return x;
}

Book* BookFind(const resizableArray<Book> &arr, const size_t &n, const Book &query) {
    int l = 0, r = static_cast<int>(n) - 1, mid, ans = -1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (arr[mid].getISBN() < query.getISBN()) {
            r = mid - 1;
        } else if (arr[mid].getISBN() > query.getISBN()) {
            l = mid + 1;
        } else {
            ans = mid;
            break;
        }
    }
    if (ans == -1) return nullptr;
    return const_cast<Book*>(&arr[ans]);
}

void sortBooksByTitle(resizableArray<Book> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].getTitle() > arr[j + 1].getTitle()) {
                Book temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortBooksByISBN(resizableArray<Book> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                Book temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortBooksByTitle(resizableArray<Book*> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] != nullptr && arr[j + 1] != nullptr) {
                if (arr[j]->getTitle() > arr[j + 1]->getTitle()) {
                    Book* temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

