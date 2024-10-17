#pragma once
#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <vector>
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
    int sachbimuon;
public:
    Book(string isbn, string title, string subject, string author,
        string publisher, Date date, int pages, int copies);
    string getIsbn() const;
    void setbook(int value);
    void setsachbimuon(int value) { sachbimuon = value; }
    int getsosachmuon() const;
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
    int bookCount;    // Số lượng sách hiện tại

public:
    BookManager() : bookCount(0) {} // Khởi tạo vector rỗng

    // Thêm sách vào vector
    vector<Book*> getbooks() { return books; }
    void addBook(Book* book) {
        books.push_back(book);
        bookCount++;
    }
    int findbook(Book* book)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i] == book)
            {
                return i; 
            }
        }
        return -1; 
    }

    void rmbook(Book* book)
    {
        int index = findbook(book);  
        if (index == -1)
        {
            cout << "Book not found!" << endl;
            return;
        }

        Book* rmbook = books[index]; 

        if (rmbook->getsosachmuon() > 0)
        {
            cout << "Sách đang có người mượn, không thể xóa!" << endl;
            return;
        }
        cout << books.size();
        books.erase(books.begin() + index);
        cout << books.size();
        bookCount--;
        delete rmbook;
    }
    
    void deleteAllBooks() {
        for (Book* book : books) {
            delete book;  // Xóa từng sách
        }
        books.clear();
        bookCount = 0;
    }

    ~BookManager() {
        deleteAllBooks();  // Xóa tất cả các sách khi quản lý trung tâm bị hủy
    }
};

#endif // BOOK_H
