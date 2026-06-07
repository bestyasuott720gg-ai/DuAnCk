#include "Invoice.h"
#include <sstream>
#include <iomanip>
#include <iostream>

// ── InvoiceItem ──────────────────────────────────────────────
string InvoiceItem::serialize() const {
    ostringstream oss;
    oss << productId << "~" << productName << "~"
        << quantity  << "~"
        << fixed << setprecision(2) << unitPrice << "~" << importPrice;
    return oss.str();
}

InvoiceItem InvoiceItem::deserialize(const string& s) {
    InvoiceItem it;
    istringstream iss(s);
    string tok;
    int idx = 0;
    while (getline(iss, tok, '~')) {
        switch (idx++) {
            case 0: it.productId   = tok; break;
            case 1: it.productName = tok; break;
            case 2: it.quantity    = stoi(tok); break;
            case 3: it.unitPrice   = stod(tok); break;
            case 4: it.importPrice = stod(tok); break;
        }
    }
    return it;
}

// ── Invoice ──────────────────────────────────────────────────
double Invoice::totalRevenue() const {
    double s = 0;
    for (auto& it : items) s += it.subtotal();
    return s;
}

double Invoice::totalProfit() const {
    double s = 0;
    for (auto& it : items) s += (it.unitPrice - it.importPrice) * it.quantity;
    return s;
}

void Invoice::display(bool showHidden) const {
    cout << "========================================\n";
    cout << "  HOA DON: " << id << "\n";
    cout << "  Nhan vien: " << staffId  << "\n";
    cout << "  Ngay&Gio : " << datetime << "\n";
    cout << "  ----------------------------------------\n";
    cout << left << setw(10) << "Ma SP"
                 << setw(25) << "Ten SP"
                 << setw(6)  << "SL"
                 << setw(12) << "Don gia"
                 << "Thanh tien\n";
    for (auto& it : items) {
        cout << fixed << setprecision(0);
        cout << left << setw(10) << it.productId
                     << setw(25) << it.productName
                     << setw(6)  << it.quantity
                     << setw(12) << it.unitPrice
                     << it.subtotal() << " VND\n";
    }
    cout << "  ----------------------------------------\n";
    cout << fixed << setprecision(0);
    cout << "  TONG TIEN: " << totalRevenue() << " VND\n";
    if (showHidden) {
        cout << "  DOANH THU: " << totalRevenue() << " VND\n";
        cout << "  LOI NHUAN: " << totalProfit()  << " VND\n";
    }
    cout << "========================================\n";
}

void Invoice::displayShort() const {
    cout << fixed << setprecision(0);
    cout << left
         << setw(12) << id
         << setw(12) << staffId
         << setw(20) << datetime
         << totalRevenue() << " VND\n";
}

// ── Serialize / Deserialize ──────────────────────────────────
// Format: id|staffId|datetime|item1;item2;...
string Invoice::serialize() const {
    ostringstream oss;
    oss << id << "|" << staffId << "|" << datetime << "|";
    for (size_t i = 0; i < items.size(); ++i) {
        oss << items[i].serialize();
        if (i + 1 < items.size()) oss << ";";
    }
    return oss.str();
}

Invoice Invoice::deserialize(const string& line) {
    Invoice inv;
    istringstream iss(line);
    string tok;
    int idx = 0;
    while (getline(iss, tok, '|')) {
        switch (idx++) {
            case 0: inv.id       = tok; break;
            case 1: inv.staffId  = tok; break;
            case 2: inv.datetime = tok; break;
            case 3: {
                istringstream itemStream(tok);
                string itemStr;
                while (getline(itemStream, itemStr, ';'))
                    if (!itemStr.empty())
                        inv.items.push_back(InvoiceItem::deserialize(itemStr));
                break;
            }
        }
    }
    return inv;
}
