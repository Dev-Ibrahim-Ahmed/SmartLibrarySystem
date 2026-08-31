#include "funcs.h"

// Helper function for case-insensitive substring searching
static string toLower(const string &s) {
    string res = s;
    transform(res.begin(), res.end(), res.begin(), [](unsigned char c){ return tolower(c); });
    return res;
}

resizableArray<Book*> BookFind(resizableArray<Book> &arr, const string &query) {
    resizableArray<Book*> matches;
    string qLower = toLower(query);

    for (size_t i = 0; i < arr.size(); i++) {
        string title = toLower(arr[i].getTitle());
        string author = toLower(arr[i].getAuthor());
        string category = toLower(arr[i].getCategory());
        string isbn = toLower(arr[i].getISBN());

        if (title.find(qLower) != string::npos ||
            author.find(qLower) != string::npos ||
            category.find(qLower) != string::npos ||
            isbn.find(qLower) != string::npos) {
            matches.addItem(&arr[i]);
        }
    }
    return matches;
}

Book* BookFind(resizableArray<Book> &arr, const Book &query) {
    // Requires catalog to be sorted by ISBN first!
    sortBooksByISBN(arr);

    int l = 0, r = (int)arr.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid].getISBN() == query.getISBN()) {
            return &arr[mid];
        }
        if (arr[mid].getISBN() < query.getISBN()) {
            l = mid + 1; // Search right half
        } else {
            r = mid - 1; // Search left half
        }
    }
    return nullptr;
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