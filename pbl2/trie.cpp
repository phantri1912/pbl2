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
    books.push_back(newBook);  
}

void TrieNode::printBooks() const {
    for (const auto& book : books) {
        cout << book->getSubject() << endl;
    }
}
TrieNode* TrieNode::returnnode(int i)
{
    return children[i];
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
void Trie::xoanode(const string& str, Book* book)
{
    TrieNode* n = search(str);
    if (!n|| n->books.size()==0) {
        cout << "Node not found!" << endl;
        return;
    }
    int i = 0;
    while (i <= n->books.size() && n->books[i] != book) {
        i++;
    }

    if (i > n->books.size()) {
        cout << "Book not found!" << endl;
        return;
    }

    int length = str.length();
    bool* indexneedfree_isbn = new bool[length+1];
    TrieNode** nodeneedfree_isbn = new TrieNode * [length+1];

    n->books.erase(n->books.begin() + i);

    if (n->books.size()==0)
    {
        TrieNode* rmnode = root;
        int y = 0;

        for (char digit : str)
        {
            indexneedfree_isbn[y] = true;
            nodeneedfree_isbn[y] = rmnode;
            int index=37;

            // Tính chỉ mục index dựa trên kí tự digit
            if (isalpha(digit)) {
                index = tolower(digit) - 'a';
            }
            else if (isdigit(digit)) {
                index = digit - '0' + 26;
            }
            else if (isspace(digit)) {
                index = 36;
            }

            for (int z = 0; z < 37; z++) {
                if (rmnode->children[z] != nullptr && z != index) {
                    indexneedfree_isbn[y] = false; // Không thể xóa nếu có nhánh khác
                    break;
                }
            }
            y++;
            rmnode = rmnode->children[index]; // Đi sâu vào node tiếp theo
        }
        indexneedfree_isbn[y] = true;
        nodeneedfree_isbn[y] = rmnode;
        for (int z = 0; z < 37; z++) {
            if (rmnode->children[z] != nullptr) {
                indexneedfree_isbn[y] = false; // Không thể xóa nếu có nhánh khác
                break;
            }
        }
        int x;
        
        for (x = length + 1; x > 0;x-- ) {
            if (indexneedfree_isbn[x] != true) {
                x++;
                break;
            }
            
        }
        n = root;
        y = 0;
        for (char digit : str)
        {
            int index;
            if (isalpha(digit)) {
                index = tolower(digit) - 'a';
            }
            else if (isdigit(digit)) {
                index = digit - '0' + 26;
            }
            else if (isspace(digit)) {
                index = 36;
            }
            if (y == x-1) {
                deleteTrie(n->children[index]); 
                n->children[index] = nullptr;
                break;
            }

            n = n->children[index]; // Đi tới node con tiếp theo
            y++;
        }
    }

    // Giải phóng bộ nhớ động
    delete[] indexneedfree_isbn;
    delete[] nodeneedfree_isbn;
}



TrieNode::~TrieNode() {
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
        else if (isspace(digit)) {
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
        else if (isspace(digit)) {
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



void Trie::printAllBooksFromNode(TrieNode* node) {
    if (!node) return;

    for (int i = 0; i < 37; ++i) {
        if (node->children[i]) {
            printAllBooksFromNode(node->children[i]);
        }
    }
    node->printBooks();
}
bool check(string str)
{
    for (char digit : str) {
        int index;
        if (isalpha(digit) || isdigit(digit) || isspace(digit))
        {

        }
        else {
            return false;
        }
    }
    return true;
}
bool check(string isbn, string title, string subject, string author, string publisher)
{
    if (check(isbn) && check(title) && check(subject) && check(author) && check(publisher))
        return true;
    else return false;
}
