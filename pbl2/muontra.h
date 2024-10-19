#ifndef MUONTRA_H
#define MUONTRA_H

#include <iostream>
#include <string>
#include <vector> // Thêm thư viện vector
#include "thoigian.h"

using namespace std;

class nguoimuon {
private:
    string isbn[3]; // Tối đa 3 sách
    Date* ngaymuon[3];
    Date* ngaytra[3];
    string id;
    int countbook; // Số lượng sách hiện đang mượn

public:
    nguoimuon(const string& isbn,  Date* ngaymuon,  Date* ngaytra, const string& id);
    string getisbn(int index) const;
    Date getngaymuon(int index) ;
    Date getngaytra(int index) ;
    string getid() const;
    int getcountbook() const;
    bool trasach(int i);
    bool addbook(const string& newisbn, Date* newngaymuon, Date* newngaytra);
    void hienthi() const;
};

// Lớp MuonTra để quản lý danh sách các người mượn
class MuonTra {
private:
    vector<nguoimuon*> dsid; // Sử dụng vector thay vì mảng con trỏ
    int soLuonguser;         // Số lượng người dùng hiện tại
    int count;              // Tổng số người mượn đã được quản lý

public:
    MuonTra();
    void hienThiSach() const;
    int kiemtraid(const string& id);
    void addarray(nguoimuon* user);
    bool add(const string& iduser, const string& idbook);
    bool add2(const string& iduser, const string& idbook, Date* ngaymuon, Date* ngaytra);
    void sortUsers();
    void sortadd();
    nguoimuon* getnguoimuon(int t) { return dsid[t]; };
    friend void ghifilemuontra(MuonTra* tt);
    ~MuonTra();
};

#endif
