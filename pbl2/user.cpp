#include "user.h"
#include <iostream>
using namespace std;

// User
User::User(string id, const string& matkhau)
    : id(id), matkhau(matkhau) {}

string User::getId() const { return id; }
string User::getMatkhau() const { return matkhau; }
void User::setMatkhau(const string& newMatkhau) { matkhau = newMatkhau; }

void User::muonsach(Book* book, MuonTra* array)
{
    if (book->getCopies() == 0)
    {
        cout << "Không thể mượn vì hết sách";
        return;
    }
    array->add(id, book->getIsbn());
}

// Admin
Admin::Admin(string id, const string& matkhau)
    : User(id, matkhau) {}

void Admin::themsach(Trie& trie) {
    string isbn, title, subject, author, publisher;
    int pages, copies;

    cout << "Nhập ISBN: ";
    getline(cin, isbn);
    cout << "Nhập tên sách: ";
    getline(cin, title);
    cout << "Nhập thể loại: ";
    getline(cin, subject);
    cout << "Nhập tên tác giả: ";
    getline(cin, author);
    cout << "Nhập tên nhà xuất bản: ";
    getline(cin, publisher);

    int ngay = 1, thang = 1, nam = 1;
    do {
        cout << "Nhập ngày: ";
        cin >> ngay;
        cout << "Nhập tháng: ";
        cin >> thang;
        cout << "Nhập năm: ";
        cin >> nam;
    } while (!kiemtrangay(ngay, thang, nam));

    Date* date = new Date(ngay, thang, nam);

    cout << "Nhập số trang: ";
    cin >> pages;
    cout << "Nhập số bản: ";
    cin >> copies;

    Book* book = new Book(isbn, title, subject, author, publisher, *date, pages, copies);
    trie.insert(isbn, book);

    cout << "Đã thêm sách thành công.\n";
    delete date;
}


void Manguser::printallUsers() {
    for (const auto& user : manguser) {
        if (user != nullptr) {
            cout << user->getId() << endl;
        }
    }
}

void Manguser::sortUsers() {
    for (size_t i = 0; i < manguser.size() - 1; i++) {
        for (size_t j = i + 1; j < manguser.size(); j++) {
            if (manguser[j]->getId() < manguser[i]->getId()) {
                swap(manguser[i], manguser[j]);
            }
        }
    }
}


void Manguser::sortadd() {
    int i = manguser.size() ;
    while (i >= 0 && manguser.back()->getId() < manguser[i]->getId()) {
        i--;
    }
    User* temp = manguser.back();
    for (int j = manguser.size() - 1; j > i + 1; j--) {
        manguser[j] = manguser[j - 1];
    }

    manguser[i + 1] = temp;
}

int Manguser::binarySearchuser(const string& id) {
    int left = 0, right = manguser.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (manguser[mid]->getId() == id) {
            return mid; // Tìm thấy User
        }
        if (manguser[mid]->getId() < id) {
            left = mid + 1; // Tìm kiếm nửa phải
        }
        else {
            right = mid - 1; // Tìm kiếm nửa trái
        }
    }
    return -1; // Không tìm thấy
}
int Manguser::binarySearchadmin(const string& id) {
    int left = 0, right = mangadmin.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mangadmin[mid]->getId() == id) {
            return mid; // Tìm thấy User
        }
        if (mangadmin[mid]->getId() < id) {
            left = mid + 1; // Tìm kiếm nửa phải
        }
        else {
            right = mid - 1; // Tìm kiếm nửa trái
        }
    }
    return -1; // Không tìm thấy
}
bool checkacount(string id, string mk,bool flag)
{
    for (char digit : id) {
        int index;
        if (isalpha(digit) || isdigit(digit))
        {

        }
        else {
            return false;
        }
    }
    for (char digit : mk) {
        int index;
        if (isalpha(digit) || isdigit(digit))
        {

        }
        else {
            return false;
        }
    }

    return true;
}
