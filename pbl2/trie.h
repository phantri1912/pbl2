﻿#pragma once
#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include "book.h"

class TrieNode {
public:
    TrieNode* children[37];
    std::vector<Book*> books;  // Thay mảng tĩnh bằng vector
    // Không cần bookCount và bookCapacity nữa

    TrieNode();
    void addBook(Book* newBook);
    void printBooks() const;
    ~TrieNode();

private:
    // Không cần resizeBooks nữa
};

class Trie {
private:
    TrieNode* root;

public:
    Trie();
    void insert(const std::string& str, Book* book);
    TrieNode* search(const std::string& str);
    void printBooksFromCode(const std::string& code);
    void printAllBooks();
    TrieNode* getroot() { return root; }
    ~Trie();

private:
    void deleteTrie(TrieNode* node);
    void printAllBooksFromNode(TrieNode* node);
};

#endif // TRIE_H
