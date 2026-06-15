#pragma once
#include<iostream>
#include<vector>
#include "taikhoan.h"
#include "quanlybanhang.h"
using namespace std;
class QuanLyTaiKhoan {
    vector<taikhoan> DanhSachTaiKhoan;
    taikhoan hientai;
public:
    void laythongtindanhsach();
    void menuquanlytaikhoan();
    bool dangnhap();
    bool kiemtravaitro();
    void doimatkhau();
    void themtaikhoan();
    void xoataikhoan();
    void danhsachtaikhoan();
    void dangxuat();
    taikhoan gettaikhoanhientai();
};
