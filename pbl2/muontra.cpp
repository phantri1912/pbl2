#include "muontra.h"
#include <iostream>
using namespace std;

// Triển khai các phương thức của lớp nguoimuon
nguoimuon::nguoimuon(const string& isbn1, const Date& ngaymuon1, const Date& ngaytra1, const string& id)
    : id(id), countbook(1)  // Khởi tạo countbook với 1 khi tạo mới
{
    isbn[0] = isbn1;
    ngaymuon[0] = ngaymuon1;
    ngaytra[0] = ngaytra1;
}

string nguoimuon::getisbn(int index) const {
    if (index >= 0 && index < 3) {
        return isbn[index];
    }
    return ""; // Trả về chuỗi rỗng nếu index không hợp lệ
}
bool nguoimuon::trasach(int i) {
    // Kiểm tra chỉ số hợp lệ
    if (i < 0 || i >= countbook) {
        return false; // Trả về false nếu chỉ số không hợp lệ
    }

    // In thông tin sách để gỡ lỗi
    std::cout << "Đang trả sách có chỉ số: " << i << std::endl;

    // Xử lý khi chỉ còn một sách
    if (countbook == 1) {
        countbook--;
        return true;
    }

    // Di chuyển sách từ vị trí i đến vị trí cuối cùng
    for (int j = i; j < countbook - 1; j++) {
        isbn[j] = isbn[j + 1];
        ngaymuon[j] = ngaymuon[j + 1];
        ngaytra[j] = ngaytra[j + 1];
    }

    // Giảm số lượng sách
    countbook--;

    return true;
}
Date nguoimuon::getngaymuon(int index) const {
    if (index >= 0 && index < 3) {
        return ngaymuon[index];
    }
    return Date(); // Trả về đối tượng Date mặc định nếu index không hợp lệ
}

Date nguoimuon::getngaytra(int index) const {
    if (index >= 0 && index < 3) {
        return ngaytra[index];
    }
    return Date(); // Trả về đối tượng Date mặc định nếu index không hợp lệ
}

string nguoimuon::getid() const { return id; }

int nguoimuon::getcountbook() const { return countbook; }

bool nguoimuon::addbook(const string& newisbn, const Date& newngaymuon, const Date& newngaytra) {
    if (countbook < 3) {
        isbn[countbook] = newisbn;
        ngaymuon[countbook] = newngaymuon;
        ngaytra[countbook] = newngaytra;
        countbook++;  // Tăng biến đếm sách đã mượn
        return true;
    }
    return false;  // Không thể mượn thêm nếu đã đạt tối đa 3 sách
}

// Triển khai các phương thức của lớp MuonTra
MuonTra::MuonTra() : soLuonguser(0), count(0) {}

void MuonTra::hienThiSach() const {
    for (const auto& user : dsid) {
        cout << "ID Người mượn: " << user->getid() << endl;
        cout << "Số sách đã mượn: " << user->getcountbook() << endl;
        for (int j = 0; j < user->getcountbook(); ++j) {
            cout << "  - Sách ISBN: " << user->getisbn(j) << endl;
            cout << "    Ngày mượn: " << user->getngaymuon(j).getngay() << "/"
                << user->getngaymuon(j).getthang() << "/"
                << user->getngaymuon(j).getnam() << endl;
            cout << "    Ngày trả: " << user->getngaytra(j).getngay() << "/"
                << user->getngaytra(j).getthang() << "/"
                << user->getngaytra(j).getnam() << endl;
        }
        cout << endl;
    }
}

void nguoimuon::hienthi() const {
    // Triển khai hiển thị chi tiết thông tin của nguoimuon
}

int MuonTra::kiemtraid(const string& id) {
    int left = 0, right = soLuonguser - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (dsid[mid]->getid() == id) {
            return mid; // Tìm thấy User
        }
        if (dsid[mid]->getid() < id) {
            left = mid + 1; // Tìm kiếm nửa phải
        }
        else {
            right = mid - 1; // Tìm kiếm nửa trái
        }
    }
    return -1;
}

void MuonTra::addarray(nguoimuon* user) {
    dsid.push_back(user);   // Thêm người mượn vào vector
    soLuonguser++;          // Tăng biến đếm người mượn
    count++;               // Tăng biến đếm tổng số người mượn
}

bool MuonTra::add(const string& iduser, const string& idbook) {
    Date today;  // Giả sử bạn có thể lấy ngày hiện tại
    Date dueDate; // Giả sử bạn có thể tính toán ngày trả

    int index = kiemtraid(iduser);
    if (index != -1) {
        // Người dùng đã tồn tại, thêm thông tin sách mượn
        if (!dsid[index]->addbook(idbook, today, dueDate)) {
            return false;
        }
    }
    else {
        // Người dùng chưa tồn tại, tạo mới
        nguoimuon* newUser = new nguoimuon(idbook, today, dueDate, iduser);
        addarray(newUser);
    }
    return true;
}

void MuonTra::sortUsers() {
    for (int i = 0; i < soLuonguser - 1; i++) {
        for (int j = i + 1; j < soLuonguser; j++) {
            if (dsid[j]->getid() < dsid[i]->getid()) {
                nguoimuon* temp = dsid[i];
                dsid[i] = dsid[j];
                dsid[j] = temp;
            }
        }
    }
}

void MuonTra::sortadd() {
    int i = soLuonguser - 2;
    while (i >= 0 && dsid[soLuonguser - 1]->getid() < dsid[i]->getid()) {
        i--;
    }
    nguoimuon* temp = dsid[soLuonguser - 1];
    for (int j = soLuonguser - 1; j > i + 1; j--) {
        dsid[j] = dsid[j - 1];
    }
    dsid[i + 1] = temp;
}

MuonTra::~MuonTra() {
    for (auto& user : dsid) {
        delete user;
    }
    dsid.clear(); // Xóa tất cả các phần tử trong vector
}
