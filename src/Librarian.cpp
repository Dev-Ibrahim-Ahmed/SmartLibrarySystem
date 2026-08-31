#include "Librarian.h"

Librarian::Librarian()
    : Person(), employeeId("")
{
}

Librarian::Librarian(
    int id,
    const string& name,
    const string& password,
    const string& employeeId
)
    : Person(id, name, password),
      employeeId(employeeId)
{
}

void Librarian::addBook(resizableArray<Book> &books)
{
    Book book;
    cin >> book;
    books.addItem(book);

    cout << "Book added successfully.\n";
}

void Librarian::removeBook(resizableArray<Book> &books)
{
    Book book;
    cin >> book;

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i] == book)
        {
            for (int j = i; j < books.size(); ++j) {
                books[j] = books[j + 1];
            }
            cout << "Book removed successfully.\n";
            return;
        }
    }

    cout << "Book not found.\n";
}

void Librarian::addMember(resizableArray<Person *>& members)
{
    int id;
    while (id > 0) {
        validate(id , "Enter the ID : ");
        if (id <= 0)cout << "Invalid ID";
    }
    string name , password;
    validate(name , "Enter the Name : ");
    validate(password , "Enter the Password");
    Person *p =  new Member(id , name , password);
    members.addItem(p);

    cout << "Member added successfully.\n";
}

void Librarian::removeMember(resizableArray<Person *>& members)
{

    for (int i = 0; i < members.size(); i++)
    {
        if (members[i] == )
        {
            cout << "Member removed successfully.\n";
            return;
        }
    }

    cout << "Member not found.\n";
}

void Librarian::displayBooks(const resizableArray<Book*>& books) const{
    cout << "\n===== Books =====\n";

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i] != nullptr)
            books[i]->showData();
    }
}

void Librarian::displayMembers(const resizableArray<Member*>& members) const{
    cout << "\n===== Members =====\n";

    for (int i = 0; i < members.size(); i++)
    {
        if (members[i] != nullptr)
            members[i]->displayInfo();
    }
}

string Librarian::getEmployeeId() const
{
    return employeeId;
}

void Librarian::setEmployeeId(const string& newEmployeeId)
{
    employeeId = newEmployeeId;
}

void Librarian::displayInfo() const
{
    Person::displayInfo();

    cout << "Employee ID: "
         << employeeId << endl;
}

void Librarian::displayStatistics() const
{
    cout << "Librarian: " << name << endl;
    cout << "Employee ID: " << employeeId << endl;
}