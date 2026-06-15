#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "hoadon.h"
using namespace std;
class QuanLyBanHang {
    vector<hoadon> DanhSachHoaDon;
    public:
        void menuquanlybanhang();
        void themHoaDon(); 
        void xuatdanhsachhoadon();
        void xuathoadongiay(); void xuathoadondientu();
        void tinhtongdoanhthu();
        void tinhloinhuan();
};