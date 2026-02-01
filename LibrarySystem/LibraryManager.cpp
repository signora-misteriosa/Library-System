#include "LibraryManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

LibraryManager::LibraryManager(string file) {
    filename = file;
}

// ---------- HELPERS ----------
vector<Book> LibraryManager::loadBooks() {
    vector<Book> books;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        books.push_back(Book::fromFileString(line));
    }
    file.close();
    return books;
}

void LibraryManager::saveBooks(const vector<Book>& books) {
    ofstream file(filename);
    for (const auto& b : books) {
        file << b.toFileString() << endl;
    }
    file.close();
}

// ---------- MENU ----------
void LibraryManager::showMenu() {
    int choice;
    do {
        cout << "\n--- Library Menu ---\n";
        cout << "1. Add book\n";
        cout << "2. Display books\n";
        cout << "3. Search by ID\n";
        cout << "4. Delete book\n";
        cout << "5. Update book\n";
        cout << "6. Sort by title\n";
        cout << "7. Export to CSV\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addBook(); break;
        case 2: displayBooks(); break;
        case 3: searchById(); break;
        case 4: deleteBook(); break;
        case 5: updateBook(); break;
        case 6: sortByTitle(); break;
        case 7: exportToCSV(); break;
        }
    } while (choice != 0);
}

// ---------- FEATURES ----------
void LibraryManager::addBook() {
    int id, year;
    string title, author;

    cout << "ID: ";
    cin >> id;
    cin.ignore();

    cout << "Title: ";
    getline(cin, title);

    cout << "Author: ";
    getline(cin, author);

    cout << "Year: ";
    cin >> year;

    ofstream file(filename, ios::app);
    file << Book(id, title, author, year).toFileString() << endl;
    file.close();

    cout << "Book added!\n";
}

void LibraryManager::displayBooks() {
    auto books = loadBooks();

    cout << "\n--- Books ---\n";
    for (auto& b : books) {
        cout << b.getId() << " | "
            << b.getTitle() << " | "
            << b.getAuthor() << " | "
            << b.getYear() << endl;
    }
}

void LibraryManager::searchById() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    auto books = loadBooks();
    for (auto& b : books) {
        if (b.getId() == id) {
            cout << "Found: " << b.getTitle() << endl;
            return;
        }
    }
    cout << "Book not found.\n";
}

void LibraryManager::deleteBook() {
    int id;
    cout << "ID to delete: ";
    cin >> id;

    auto books = loadBooks();
    auto oldSize = books.size();

    books.erase(remove_if(books.begin(), books.end(),
        [id](Book& b) { return b.getId() == id; }),
        books.end());

    saveBooks(books);

    cout << (books.size() < oldSize ? "Deleted.\n" : "Not found.\n");
}

void LibraryManager::updateBook() {
    int id;
    cout << "ID to update: ";
    cin >> id;
    cin.ignore();

    auto books = loadBooks();
    for (auto& b : books) {
        if (b.getId() == id) {
            string title, author;
            int year;

            cout << "New title: ";
            getline(cin, title);
            cout << "New author: ";
            getline(cin, author);
            cout << "New year: ";
            cin >> year;

            b = Book(id, title, author, year);
            saveBooks(books);
            cout << "Updated!\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void LibraryManager::sortByTitle() {
    auto books = loadBooks();
    sort(books.begin(), books.end(),
        [](Book& a, Book& b) {
            return a.getTitle() < b.getTitle();
        });
    saveBooks(books);
    cout << "Sorted by title.\n";
}

void LibraryManager::exportToCSV() {
    auto books = loadBooks();
    ofstream file("books.csv");

    file << "ID,Title,Author,Year\n";
    for (auto& b : books) {
        file << b.getId() << ","
            << b.getTitle() << ","
            << b.getAuthor() << ","
            << b.getYear() << "\n";
    }
    file.close();

    cout << "Exported to books.csv\n";
}
