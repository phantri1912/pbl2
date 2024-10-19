#pragma once
#ifndef USER_H
#define USER_H

#include "thoigian.h"
#include <string>
#include <vector>  // Thêm thư viện vector
#include "trie.h"
#include "muontra.h"
using namespace std;

class User {
private:
    string id;
    string matkhau;
public:
    User(string id, const string& matkhau);
    string getId() const;
    string getMatkhau() const;
    void setMatkhau(const string& newMatkhau);
    void muonsach(Book* book, MuonTra* array);
};

class Admin : public User {
public:
    Admin(string id, const string& matkhau);
    void themsach(Trie& trie);
};
class Manguser {
private:
    vector<User*> manguser;  // Quản lý các User
    vector<Admin*> mangadmin;  // Quản lý các Admin
public:
    Manguser() = default;
    friend void ghifileuser(Manguser* m);
    // Thêm User
    void adduser(User* p) {
        manguser.push_back(p);
    }

    // Thêm Admin
    void addadmin(Admin* p) {
        mangadmin.push_back(p);
    }

    // Truy cập admin
    Admin* getadmin(int i) {
        return mangadmin[i];
    }

    // Truy cập user
    User* getuser(int i) {
        return manguser[i];
    }
    void sortadd();
    void printallUsers();
    void sortUsers();

    int binarySearchuser(const string& id);
    int binarySearchadmin(const string& id);
    ~Manguser() {
        for (User* u : manguser) {
            delete u;
        }
        for (Admin* a : mangadmin) {
            delete a;
        }
    }
};
extern bool checkacount(string id, string mk);



#endif // USER_H
