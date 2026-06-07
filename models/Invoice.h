#pragma once
#include <string>
#include <vector>
using namespace std;

// ============================================================
//  Dòng sản phẩm trong hóa đơn
// ============================================================
struct InvoiceItem {
    string productId;
    string productName;
    int    quantity;
    double unitPrice;    // Giá tại thời điểm bán
    double importPrice;  // Giá nhập tại thời điểm bán

    double subtotal()  const { return unitPrice   * quantity; }
    double costTotal() const { return importPrice * quantity; }

    string serialize()   const;
    static InvoiceItem deserialize(const string& s);
};

// ============================================================
//  Hóa đơn
// ============================================================
struct Invoice {
    string id;           // Mã hóa đơn
    string staffId;      // Mã nhân viên
    string datetime;     // Ngày & giờ
    vector<InvoiceItem> items;

    double totalRevenue() const;
    double totalProfit()  const;

    void display(bool showHidden = false) const;
    void displayShort() const;

    string serialize()   const;
    static Invoice deserialize(const string& line);
};
