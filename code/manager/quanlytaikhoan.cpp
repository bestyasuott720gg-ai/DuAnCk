#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <cstdlib> 
#include "quanlytaikhoan.h"
#include "main.h"
using namespace std;
void QuanLyTaiKhoan::laythongtindanhsach(){
    ifstream fin("danhsachtaikhoan.txt");
    while(fin>>DanhSachTaiKhoan.back().tendangnhap>>DanhSachTaiKhoan.back().matkhau);
    fin.close();
}

void QuanLyTaiKhoan::menuquanlytaikhoan(){
    system("cls");
    int chonmenu;
    while(true){
    cout<<"1. them tai khoan"<<endl; cout<<"2. xoa tai khoan"<<endl;
    cout<<"3. doi mat khau"<<endl; cout<<"4. danh sach tai khoan" <<endl;
    cout<<"5. thoat"<<endl;
    cout<<"nhap lua chon: "; cin>>chonmenu; 
    switch(chonmenu){
        case 1: themtaikhoan(); break;
        case 2: xoataikhoan(); break;
        case 3: doimatkhau(); break;
        case 4: danhsachtaikhoan(); break;
        case 5: return; break;        
    }
    }
}
bool QuanLyTaiKhoan::dangnhap(){
    system("cls"); 
    string tentaikhoan, mk;
    cout << "Nhap ten dang nhap: ";
    cin >> tentaikhoan;
    cout << "Nhap mat khau: ";
    cin >> mk;
    for (const auto& tk : DanhSachTaiKhoan) {
        if(tk.tendangnhap==tentaikhoan&&tk.matkhau==mk){
            hientai.tendangnhap=tk.tendangnhap;
            hientai.matkhau=tk.matkhau;
            hientai.vaitro=tk.vaitro;
            cout << "Dang nhap thanh cong!" << endl;
            return true;
        }
    }
    cout << "Ten dang nhap hoac mat khau sai!" << endl;
    return false;
}
bool QuanLyTaiKhoan::kiemtravaitro(){
    return (hientai.vaitro=="chu") ? true:false;
}

void QuanLyTaiKhoan::doimatkhau() {
    system("cls"); 
    string tenDangNhap, matKhauCu, matKhauMoi;
    while(true){
    cout<<"Nhap ten dang nhap: "; cin>>tenDangNhap;
    cout<<"Nhap mat khau cu: "; cin>>matKhauCu;
    for (auto& tk : DanhSachTaiKhoan) {
        if (tk.tendangnhap == tenDangNhap && tk.matkhau == matKhauCu) {
            cout << "Nhap mat khau moi: ";
            cin >> matKhauMoi;
            tk.matkhau = matKhauMoi;
            cout << "Doi mat khau thanh cong!" << endl;
            return;
        }
    cout << "Ten dang nhap hoac mat khau sai!" << endl;
    cout << "Nhap lai tai khoan hoac mat khau!"<<endl;
    }
    }
}
void QuanLyTaiKhoan::themtaikhoan(){
    system("cls");
    ofstream fout("danhsachtaikhoan.txt"); //chua chot ten file
    taikhoan a; string matkhauxacminh;
    cout<<"nhap ten dang nhap moi\n"; cin>>a.tendangnhap;
    cout<<"nhap mat khau moi\n"; cin>>a.matkhau;
    do{
    cout<<"nhap lai mat khau de xan minh\n"; cin>>matkhauxacminh;
    } while(a.matkhau!=matkhauxacminh);
    DanhSachTaiKhoan.push_back(a); 
    fout<<a.tendangnhap<<" || "<< a.matkhau<<endl;
    fout.close();
    if(trove()==true) return;
}
void QuanLyTaiKhoan::xoataikhoan(){
    while(true) {
        system("cls");
        string tenXoa;
        cout << "Nhap TEN DANG NHAP cua tai khoan muon xoa: ";
        cin >> tenXoa;

        bool timThay = false;

        // 1. Duyệt vector DanhSachTaiKhoan bằng iterator để có thể xóa
        for (auto it = DanhSachTaiKhoan.begin(); it != DanhSachTaiKhoan.end(); ++it) {
            if (it->tendangnhap == tenXoa) { // Tìm chính xác theo Tên đăng nhập
                DanhSachTaiKhoan.erase(it); // Xóa thẳng phần tử này ra khỏi vector
                timThay = true;
                cout << "Xoa tai khoan thanh cong!" << endl;
                break; // Thoát khỏi vòng for vì đã xóa xong
            }
        }

        if (!timThay) {
            cout << "Khong tim thay tai khoan can xoa!" << endl;
        } else {
            // 2. Cập nhật lại file .txt (Ghi đè lại danh sách mới sau khi xóa)
            ofstream fout("danhsachtaikhoan.txt", ios::trunc); // ios::trunc để xóa hết file cũ ghi lại từ đầu
            for (const auto& tk : DanhSachTaiKhoan) {
                fout << tk.tendangnhap << " | " << tk.matkhau << endl;
            }
            fout.close();
        }
        if (trove() == true) return;
    }
}
void QuanLyTaiKhoan::danhsachtaikhoan(){
    system("cls");
    ifstream fin("danhsachtaikhoan.txt");
    string dong;
    while(getline(fin,dong)){
        cout<<dong<<endl;
    }
    fin.close();
     if (trove() == true) return;
}

void QuanLyTaiKhoan::dangxuat(){
     dangnhap();
}
taikhoan QuanLyTaiKhoan::gettaikhoanhientai(){
    return this->hientai;
}