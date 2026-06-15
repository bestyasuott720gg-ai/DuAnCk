#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include "hoadon.h"
using namespace std;
sanphamtronghoadon::sanphamtronghoadon() {
        masanpham = "";
        tensanpham = "";
        soluong = 0;       // Đảm bảo không bị dính số rác
        giaban = 0.0;     // Đảm bảo không bị dính số rác
        gianhap = 0.0;    // Đảm bảo không bị dính số rác
    }
hoadon::hoadon(){
    mahoadon=" ";
    ngaygio=" ";
} 
void hoadon::layngaygiohientai() {
    time_t now = time(0);
    tm *ltm = localtime(&now); 
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", ltm);
    ngaygio = string(buffer); 
}
double hoadon::tongtien(){
    double tong=0;
    for(int i=0; i<sphd.size(); i++){
        if(sphd[i].soluong!=0)
        tong+=sphd[i].tinhtien();
    }
    return tong;
}

double hoadon::tongsoluong(){
    double tong=0;
    for(int i=0; i<sphd.size(); i++){
        if(sphd[i].soluong!=0) tong+=sphd[i].soluong;
    }
    return tong;
}
void hoadon::inthongtinmoisanpham(){
    ofstream fout(mahoadon + ".txt", ios::app);
    for(int a=0; a<sphd.size(); a++){
       if(sphd[a].soluong!=0){
           fout<<sphd[a].masanpham<<"    "<< sphd[a].tensanpham<< "         "<<sphd[a].giaban<<"           "<<sphd[a].soluong<<endl;
        }
    }
    fout.close();
}
void hoadon::soluongmoisanpham(){ 
    for(int a=0; a<sphd.size(); a++){
            for(int j=a+1; j<sphd.size(); j++){
                if(sphd[a].masanpham==sphd[j].masanpham&&sphd[a].soluong!=0){
                    sphd[a].soluong+=sphd[j].soluong;
                    sphd[j].soluong=0;
            }
        }
    }
}
double hoadon::tongchiphi(){
    double chiphi=0;
    for(int i=0; i<sphd.size(); i++){
        if(sphd[i].soluong!=0) chiphi+=sphd[i].tinhchiphi();
    }
    return chiphi;
}
double sanphamtronghoadon::tinhtien(){ return soluong * giaban; }
double sanphamtronghoadon::tinhchiphi(){ return soluong * gianhap; }

