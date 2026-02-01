
#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    int year;

public:
    Book();
    Book(int, string, string, int);

    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    int getYear() const;

    string toFileString() const;
    static Book fromFileString(const string& line);
};

#endif
