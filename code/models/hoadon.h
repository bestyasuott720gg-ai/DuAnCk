#pragma once
#include<string>
#include<vector>
using namespace std;
struct sanphamtronghoadon{
        string masanpham;
        string tensanpham;
        int soluong;
        double giaban;
        double gianhap;
        sanphamtronghoadon();
        double tinhtien();
        double tinhchiphi();
};
struct hoadon{
        vector<sanphamtronghoadon> sphd;
        string mahoadon;
        static string tennhanvien;
        string ngaygio;
        hoadon();
        void layngaygiohientai();
        void inthongtinmoisanpham();
        void soluongmoisanpham();
        double tongsoluong();
        double tongtien();
        double tongchiphi();
        //hàm lấy ngày giờ hiện tại
}; 
