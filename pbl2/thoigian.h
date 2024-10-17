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
    Date(bool flag);
    Date(int ngay, int thang, int nam);
    int getngay() const;
    int getthang() const;
    int getnam() const;
    bool operator <= (Date d);
};

#endif // THOIGIAN_H
