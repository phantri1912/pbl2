#include "trie.h"
#include <iostream>
#include <cctype>

using namespace std;

// TrieNode
TrieNode::TrieNode() {
    for (int i = 0; i < 37; ++i) {
        children[i] = nullptr;
    }
}

void TrieNode::addBook(Book* newBook) {
    books.push_back(newBook);  // Thêm sách vào vector
}

void TrieNode::printBooks() const {
    for (const auto& book : books) {
        cout << book->getSubject() << endl;  // Giả sử toán tử << đã được định nghĩa cho Book
    }
}

TrieNode::~TrieNode() {
    // Không cần giải phóng books vì vector tự quản lý bộ nhớ
    //for (auto book : books) {
    //    delete book;  // Giả sử các Book đã được cấp phát bằng new
    //}
    books.clear();
}

// Trie
Trie::Trie() : root(new TrieNode()) {}

void Trie::insert(const string& str, Book* book) {
    TrieNode* node = root;
    for (char digit : str) {
        int index;
        if (isalpha(digit)) {
            index = tolower(digit) - 'a';
        }
        else if (isdigit(digit)) {
            index = digit - '0' + 26;
        }
        else if (isspace(digit) || digit == '-') {
            index = 36;
        }
        else {
            index = 37; // Bỏ qua các ký tự không hợp lệ
        }
        if (index < 0 || index > 36) {
            cout << "false";
            return;
        }
        else if (node->children[index] == nullptr) {
            node->children[index] = new TrieNode();
        }
        node = node->children[index];
    }
    node->addBook(book);
}

TrieNode* Trie::search(const string& str) {
    TrieNode* node = root;
    for (char digit : str) {
        int index;
        if (isalpha(digit)) {
            index = tolower(digit) - 'a';
        }
        else if (isdigit(digit)) {
            index = digit - '0' + 26;
        }
        else if (isspace(digit) || digit == '-') {
            index = 36;
        }
        else {
            return nullptr; // Bỏ qua các ký tự không hợp lệ
        }

        if (node->children[index] == nullptr) {
            return nullptr;
        }
        node = node->children[index];
    }
    return node;
}

void Trie::printBooksFromCode(const string& code) {
    TrieNode* node = search(code);
    if (node && !node->books.empty()) {
        node->printBooks();
    }
    else {
        cout << "No books found for code " << code << endl;
    }
}

void Trie::printAllBooks() {
    printAllBooksFromNode(root);
}

Trie::~Trie() {
    deleteTrie(root);
}

void Trie::deleteTrie(TrieNode* node) {
    if (!node) return;

    for (int i = 0; i < 37; ++i) {
        if (node->children[i] != nullptr) {
            deleteTrie(node->children[i]);
            node->children[i] = nullptr;
        }
    }
    delete node;
}

void Trie::printAllBooksFromNode(TrieNode* node) {
    if (!node) return;

    for (int i = 0; i < 37; ++i) {
        if (node->children[i]) {
            printAllBooksFromNode(node->children[i]);
        }
    }
    node->printBooks();
}
