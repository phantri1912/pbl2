#include "thoigian.h"
#include <iostream>
#include <ctime>

    

using namespace std;

Date::Date(bool flag){
    int i;
    if (flag) {
        i = 1;
    }else i = 0;

    time_t hientai = time(0);
    tm ltm;
    localtime_s(&ltm, &hientai);
    int ngay = ltm.tm_mday;
    int thang = 1 + ltm.tm_mon;
    int nam = 1900 +i+ ltm.tm_year;

    if (kiemtrangay(ngay, thang,  nam)) {
        this->ngay = ngay;
        this->thang = thang;
        this->nam = nam;
    }
    else {
        cout << "Có lỗi! Hãy kiểm tra và nhập lại." << endl;
    }
}

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
    time_t hientai = time(0);
    tm ltm;
    localtime_s(&ltm, &hientai);
    int ngayhientai = ltm.tm_mday;
    int thanghientai = 1 + ltm.tm_mon;
    int namhientai = 1900 + ltm.tm_year;
    if (thang < 1 || thang > 12) {
        
        return false;
    }
    if (ngay < 1 || ngay > ngaytrongthang[thang - 1]) {
        
        return false;
    }
    if (nam == namhientai)
    {
        if (thanghientai > thang)
        {
            return false;
        }
        else if (thanghientai == thang)
        {
            return ngay <= ngayhientai;
        }
    }
    if (nam > namhientai)
    {
        
        return false;
    }

    return true;
}
bool Date::operator <= (Date d)
{
    if (nam == d.nam)
    {
        if (thang > d.thang)
        {
            return false;
        }
        else if (thang == d.thang)
        {
            return ngay < d.ngay;
        }
    }
    if (nam > d.nam)
    {
        return false;
    }
}