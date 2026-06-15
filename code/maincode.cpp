#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include "manager/quanlybanhang.h"
#include "manager/quanlytaikhoan.h"
#include "hoadon.h"

string hoadon::tennhanvien="";

int main(){
    const string ACCOUNT_FILE = "data_accounts.txt";
    const string PRODUCT_FILE = "data_products.txt";
    const string INVOICE_FILE = "data_invoices.txt";
    
    QuanLyTaiKhoan QLTK;
    QuanLyBanHang QLBH;

    int chon;
    while (true){  
    if(QLTK.dangnhap()==true){
        if(QLTK.kiemtravaitro()==true){
            hoadon::tennhanvien=QLTK.gettaikhoanhientai().tendangnhap;
        cout << "\n===== MENU CHINH =====\n";
        cout << "  Nguoi dung: " << QLTK.gettaikhoanhientai().tendangnhap
             <<" || "<< QLTK.gettaikhoanhientai().vaitro;
        cout << "  1. Thong tin san pham\n";
        cout << "  2. Quan li thong tin hang hoa\n";
        cout << "  3. Quan li ban hang\n";
        cout << "  4. Chuc nang tien ich\n";
        cout << "  5. Quan li tai khoan\n";
        cout << "  6. Canh bao hang sap het\n";
        cout << "  7. Dang xuat\n";
        cout<< "  Chon: ";
        cin>>chon;
    switch(chon){
        case 1: menuthongtinsanpham(); break;
        case 2: menuquanlithongtinsanpham(); break;
        case 3: QLBH.menuquanlybanhang(); break;
        case 4: menutienich(); break;
        case 5: QLTK.menuquanlytaikhoan(); break;
        case 6: canhbaosaphethang(); break;  
        case 7: QLTK.dangxuat(); break;        
    }
        }
    }
    }
    return 0;
}
