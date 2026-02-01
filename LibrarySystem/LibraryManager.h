#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include "Book.h"
#include <string>
#include <vector>

class LibraryManager {
private:
    string filename;

    vector<Book> loadBooks();
    void saveBooks(const vector<Book>& books);

public:
    LibraryManager(string);

    void showMenu();
    void addBook();
    void displayBooks();
    void searchById();
    void deleteBook();
    void updateBook();
    void sortByTitle();
    void exportToCSV();
};

#endif
