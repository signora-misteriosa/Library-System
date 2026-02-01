#include "Book.h"
#include <sstream>

Book::Book() : id(0), year(0) {}

Book::Book(int i, string t, string a, int y)
    : id(i), title(t), author(a), year(y) {
}

int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }

string Book::toFileString() const {
    return to_string(id) + "|" + title + "|" + author + "|" + to_string(year);
}

Book Book::fromFileString(const string& line) {
    stringstream ss(line);
    string id, title, author, year;

    getline(ss, id, '|');
    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, year, '|');

    return Book(stoi(id), title, author, stoi(year));
}
