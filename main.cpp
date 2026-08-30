#include <iostream>
#include "Book.h"
#include "Person.h"
#include "Member.h"
#include "Librarian.h"
#include "DataManager.h"
#include "resizableArray.h"
#include "funcs.h"

using namespace std;

int main() {
    resizableArray<Book> catalog;
    resizableArray<Person*> users;

    DataManager::loadBooks("data/books.json", catalog);
    DataManager::loadPersons("data/persons.json", users, catalog);

    cout << "\n--- Testing Person & Member ---" << endl;
    Member member(101, "Ahmed Abdoo", "1234", 3);
    member.displayInfo();
    cout << "Password check: " << (member.checkPassword("1234") ? "Success" : "Failed") << endl;
    cout << "Fine for 3 days late: $" << member.calculateFine(3, 2.0) << endl;

    cout << "\n--- Testing Librarian ---" << endl;
    Librarian librarian(1, "Ibrahim Al Abd", "admin123", "LIB-001");
    librarian.displayInfo();

    for (int i = 0; i < catalog.size(); i++) {
        librarian.addBook(&catalog[i]);
    }
    for (int i = 0; i < users.size(); i++) {
        Member* m = dynamic_cast<Member*>(users[i]);
        if (m != nullptr) {
            librarian.addMember(m);
        }
    }
    librarian.displayStatistics();

    cout << "\n--- Testing Sort ---" << endl;
    sortBooksByTitle(catalog);
    cout << "First book after sort: " << catalog[0].getTitle() << endl;

    return 0;
}
