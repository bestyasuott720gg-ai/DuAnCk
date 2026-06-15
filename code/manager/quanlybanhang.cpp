#include<iostream>
#include<fstream>
#include<vector>
#include <cstdlib> 
#include "main.h"
using namespace std;
#include "quanlybanhang.h"



void QuanLyBanHang::menuquanlybanhang() {
    system("cls");
    int chonmenubanhang;
    cout<<"1. them hoa don"<<endl; cout<<"2. xuat danh sach hoa don"<<endl;
    cout<<"3. tinh tong doanh thu"<<endl; cout<<"4. tinh tong loi nhuan"<<endl;
    cout<<"5. thoat"<<endl;
    cout<<"nhap lua chon: "; cin>>chonmenubanhang; 
    switch(chonmenubanhang){
        case 1: themHoaDon(); break;
        case 2: xuatdanhsachhoadon(); break;
        case 3: tinhtongdoanhthu(); break;
        case 4: tinhloinhuan(); break;
        case 5: return; break;        
    }
}
void QuanLyBanHang::xuatdanhsachhoadon() {
    system("cls");
    ifstream fin ("danhsachhoadon.txt");
    string line;
    while (fin>>line) cout<<line<<endl;
    fin.close();
    cout<<"----chon 0 de quay ve-----";
    if (trove() == true) return; 
}

void QuanLyBanHang::xuathoadondientu() {
    if(DanhSachHoaDon.size()<10) DanhSachHoaDon.back().mahoadon="HD00" + to_string(DanhSachHoaDon.size());
    else DanhSachHoaDon.back().mahoadon="HD0" + to_string(DanhSachHoaDon.size());
    ofstream fout("danhsachhoadon.txt", ios::app);
    fout<<DanhSachHoaDon.back().ngaygio<<"||"<<DanhSachHoaDon.back().mahoadon<<"||"<<DanhSachHoaDon.back().tennhanvien<<"||"<<DanhSachHoaDon.back().tongtien()<<endl;
    fout.close();
}
void QuanLyBanHang::xuathoadongiay() {
    if(DanhSachHoaDon.size()<10) DanhSachHoaDon.back().mahoadon="HD00" + to_string(DanhSachHoaDon.size());
    else DanhSachHoaDon.back().mahoadon="HD0" + to_string(DanhSachHoaDon.size());
    ofstream fout(DanhSachHoaDon.back().mahoadon + ".txt", ios::app);
    fout<<"                          ------BADMINTON SHOP------"<<endl;
    fout<<"                             HOA DON THANH TOAN"<<endl;
    fout<<" ----------------------------------------------------------------------------------"<<endl;
    fout<<" ma hoa don: "<<DanhSachHoaDon.back().mahoadon<<endl;
    fout<<" TEN NHAN VIEN: "<<DanhSachHoaDon.back().tennhanvien<<endl;//làm sau
    fout<<" NGAY GIO: "<<DanhSachHoaDon.back().ngaygio<<endl;//làm sau
    fout<<"-----------------------------------------------------------------------------------"<<endl;
    fout<<" ma san pham: "<<"   tensanpham"<<"         gia san pham"<<"           so luong"<<endl;

    DanhSachHoaDon.back().inthongtinmoisanpham();
    fout<<"tong cong:                     "<<DanhSachHoaDon.back().tongtien()<<"           "<<DanhSachHoaDon.back().tongsoluong() <<endl;
    fout<<"-----------------------------------------------------------------------------------"<<endl;
    fout<<"            cam on ban da mua hang tai cua hang chung toi!"<<endl;
    fout.close();
}

void QuanLyBanHang::themHoaDon() {
    system("cls");
    sanphamtronghoadon sp;   hoadon hd;
    int chon, xuat;
    cout<<"1. chon san pham"<<endl; cout<<"2. thoat"<<endl;
    cout<<"nhap lua chon: "; cin>>chon; 
    switch(chon){
        case 1:
            cout<<"nhap ma san pham: (CHON 0 DE THOAT) ";
            cin>>sp.masanpham;
            while(sp.masanpham!="0"){
                cout<<"nhap so luong: ";
                cin>>sp.soluong;
                hd.sphd.push_back(sp);
                cout<<"nhap ma san pham:  (CHON 0 DE THANH TOAN) ";
                cin>>sp.masanpham;
            }
            DanhSachHoaDon.push_back(hd);
            DanhSachHoaDon.back().soluongmoisanpham();
            cout<<"xuat hoa don (1_xuat/0_huy)"; cin >> xuat;
            xuathoadondientu();
            if(xuat==1) xuathoadongiay();
            cout<<"----chon 0 de quay ve-----";
            if (trove() == true) return; 
        case 2: 
            return;       
    }
}


void QuanLyBanHang::tinhtongdoanhthu() {
    system("cls");
    double tongdoanhthu=0;
    for(int i=0; i<DanhSachHoaDon.size(); i++){
        cout<< DanhSachHoaDon[i].mahoadon<<"    "<< DanhSachHoaDon[i].tennhanvien<<"    "<< DanhSachHoaDon[i].ngaygio<<"    "<< DanhSachHoaDon[i].tongtien()<<endl;
        tongdoanhthu+=DanhSachHoaDon[i].tongtien();
    }
    cout<<"tong doanh thu: "<<tongdoanhthu<<endl;
    cout<<"----chon 0 de quay ve-----";
    if (trove() == true) return; 
}
void QuanLyBanHang::tinhloinhuan() {
    system("cls");
    double loinhuan=0;
    for(int i=0; i<DanhSachHoaDon.size(); i++){
        loinhuan+=DanhSachHoaDon[i].tongtien() - DanhSachHoaDon[i].tongchiphi();
    }
    cout<<"tong loi nhuan: "<<loinhuan<<endl;
    if (trove() == true) return; 
}
         