#pragma once
#include <string>
#include <iostream>
using namespace std;

// ============================================================
//  Loại sản phẩm
// ============================================================
enum ProductType { CLOTHING, RACKET, ACCESSORY, SHUTTLECOCK };

string productTypeToStr(ProductType t);
ProductType strToProductType(const string& s);

// ============================================================
//  Cấu trúc sản phẩm chung
// ============================================================
struct Product {
    string id;           // Mã sản phẩm
    string name;         // Tên
    string brand;        // Hãng
    int    quantity;     // Số lượng tồn kho
    double salePrice;    // Giá bán
    double importPrice;  // Giá nhập
    ProductType type;    // Loại

    // Thuộc tính riêng – Quần áo
    string color;        // Màu
    string size;         // Kích thước (S/M/L/XL)
    string material;     // Chất liệu

    // Thuộc tính riêng – Vợt
    string specs;        // Thông số kỹ thuật
    string difficulty;   // Độ khó (Beginner/Intermediate/Advanced)

    Product();

    void display() const;
    void displayShort() const;

    // Serialize / deserialize để lưu file
    string serialize() const;
    static Product deserialize(const string& line);
};
