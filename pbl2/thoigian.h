#pragma once
#ifndef THOIGIAN_H
#define THOIGIAN_H
#include <iostream>
using namespace std;
bool kiemtrangay(int ngay, int thang, int nam); 
class Date {
private:
    int ngay;
    int thang;
    int nam;

public:
    Date(int ngay , int thang , int nam); 
    int getngay() const;
    int getthang() const;
    int getnam() const;
    


    Date() {
        time_t now = time(0);
        tm ltm;  // Sử dụng struct tm thay vì con trỏ
        localtime_s(&ltm, &now);  // Sử dụng localtime_s để an toàn hơn

        // Kiểm tra ngày hợp lệ
        if (kiemtrangay(ltm.tm_mday, ltm.tm_mon + 1, 1900 + ltm.tm_year)) {  // ltm.tm_mon cần +1 vì tháng bắt đầu từ 0
            this->ngay = ngay;
            this->thang = thang;
            this->nam = nam;
        }
        else {
            cout << "Có lỗi! Hãy kiểm tra và nhập lại." << endl;
        }
    }
};
#endif // THOIGIAN_H
