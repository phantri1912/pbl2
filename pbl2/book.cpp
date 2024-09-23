#include "book.h"
#include <iostream>
using namespace std;

Book::Book(string isbn, string title, string subject, string author,
    string publisher, Date date, int pages, int copies)
    : isbn(isbn), title(title), subject(subject), author(author),
    publisher(publisher), date(date), pages(pages), copies(copies) {}

string Book::getIsbn() const { return isbn; }
string Book::getTitle() const { return title; }
string Book::getSubject() const { return subject; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }
Date Book::getDate() const { return date; }
int Book::getPages() const { return pages; }
int Book::getCopies() const { return copies; }
void Book::setbook(int value) {
    copies = value;
}