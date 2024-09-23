#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector> // Thêm thư viện vector
#include "thoigian.h"
using namespace std;

class Book {
private:
    string isbn;
    string title;
    string subject;
    string author;
    string publisher;
    Date date;
    int pages;
    int copies;
public:
    Book(string isbn, string title, string subject, string author,
        string publisher, Date date, int pages, int copies);
    string getIsbn() const;
    void setbook(int value);
    string getTitle() const;
    string getSubject() const;
    string getAuthor() const;
    string getPublisher() const;
    Date getDate() const;
    int getPages() const;
    int getCopies() const;
};

class BookManager {
private:
    vector<Book*> books;   // Sử dụng vector thay vì mảng con trỏ
    int bookCount;         // Số lượng sách hiện tại
    // Không cần bookCapacity nữa

public:
    BookManager() : bookCount(0) {} // Khởi tạo vector rỗng

    // Thêm sách vào vector
    void addBook(Book* book) {
        books.push_back(book);   // Thêm sách vào vector
        bookCount++;
    }

    // Xóa tất cả các sách
    void deleteAllBooks() {
        for (Book* book : books) {
            delete book;  // Xóa từng sách
        }
        books.clear();  // Xóa tất cả các phần tử trong vector
        bookCount = 0;
    }

    ~BookManager() {
        deleteAllBooks();  // Xóa tất cả các sách khi quản lý trung tâm bị hủy
    }
};

#endif // BOOK_H
