#include "thoigian.h"
#include <iostream>
#include <ctime>

    

   

using namespace std;
Date::Date(int ngay, int thang, int nam) {
    if (kiemtrangay(ngay, thang, nam)) {
        this->ngay = ngay;
        this->thang = thang;
        this->nam = nam;
    }
    else {
        cout << "Co loi hay kiem tra va nhap lai." << endl;
    }
}

int Date::getngay() const { return ngay; }
int Date::getthang() const { return thang; }
int Date::getnam() const { return nam; }

bool kiemtrangay(int ngay, int thang, int nam) {
    int ngaytrongthang[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (thang < 1 || thang > 12) {
        cout << "Thang khong hop le" << endl;
        return false;
    }
    if (ngay < 1 || ngay > ngaytrongthang[thang - 1]) {
        cout << "Ngay khong hop le" << endl;
        return false;
    }
    if (nam > 2024)
    {
        cout << "Nam ko hop le" << endl;
        return false;
    }

    return true;
}
