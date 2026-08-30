#include <iostream>
#include <string>
#include "include/resizableArray.h"
#include "include/Book.h"
#include "include/funcs.h"
#include "include/Member.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;

resizableArray<Book> books;
resizableArray<Person *> People;

int main() {



    cout << "Press Enter to exit.....";
    cin.ignore();
    cin.get();
    return 0;
}