#include "SalesManager.h"
#include "../utils/Utils.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <algorithm>

SalesManager::SalesManager(const string& invoiceFile, ProductManager& pm)
    : dataFile(invoiceFile), pm(pm), idCounter(1) {
    loadFromFile();
}

// ── File I/O ─────────────────────────────────────────────────
void SalesManager::loadFromFile() {
    invoices.clear(); idCounter = 1;
    for (auto& line : readLines(dataFile)) {
        invoices.push_back(Invoice::deserialize(line));
        idCounter++;
    }
}

void SalesManager::saveToFile() const {
    vector<string> lines;
    for (auto& inv : invoices) lines.push_back(inv.serialize());
    writeLines(dataFile, lines);
}

// ── Tạo hóa đơn ──────────────────────────────────────────────
void SalesManager::createInvoice(const string& staffId) {
    cout << "\n===== TAO HOA DON MOI =====\n";
    Invoice inv;
    inv.id       = generateId("HD", idCounter++);
    inv.staffId  = staffId;
    inv.datetime = getCurrentDatetime();

    pm.listAll();

    while (true) {
        cout << "\n  Nhap ma SP (hoac 'done' de ket thuc): ";
        string pid;
        getline(cin, pid);
        pid = trim(pid);
        if (toLower(pid) == "done") break;

        auto* p = pm.findById(pid);
        if (!p) { cout << "  [!] Khong tim thay SP.\n"; continue; }
        if (p->quantity == 0) { cout << "  [!] San pham het hang.\n"; continue; }

        cout << "  Ten: " << p->name << "  |  Ton kho: " << p->quantity << "\n";
        int qty = inputInt("  So luong ban : ", 1, p->quantity);

        InvoiceItem item;
        item.productId   = p->id;
        item.productName = p->name;
        item.quantity    = qty;
        item.unitPrice   = p->salePrice;
        item.importPrice = p->importPrice;
        inv.items.push_back(item);

        pm.decreaseStock(pid, qty);
        cout << "  [+] Them " << qty << " x " << p->name << "\n";
    }

    if (inv.items.empty()) {
        cout << "  [!] Hoa don trong. Huy bo.\n"; return;
    }

    inv.display(false);

    cout << "  Xac nhan xuat hoa don? (y/n): ";
    char ch; cin >> ch; cin.ignore();
    if (tolower(ch) != 'y') {
        cout << "  [!] Da huy. (Ton kho da bi tru – vui long reload)\n";
        return;
    }

    invoices.push_back(inv);
    saveToFile();
    cout << "  [v] Hoa don [" << inv.id << "] da luu thanh cong.\n";
}

// ── Xem danh sách hóa đơn ────────────────────────────────────
void SalesManager::listInvoices() const {
    cout << "\n===== DANH SACH HOA DON (" << invoices.size() << ") =====\n";
    cout << "  " << left
         << setw(12) << "Ma HD"
         << setw(12) << "NV"
         << setw(20) << "Ngay&Gio"
         << "Tong tien\n";
    cout << "  " << string(60, '-') << "\n";
    for (auto& inv : invoices) {
        cout << "  "; inv.displayShort();
    }
}

void SalesManager::viewInvoice() const {
    string id = inputNonEmpty("  Ma hoa don: ");
    for (auto& inv : invoices)
        if (inv.id == id) { inv.display(false); return; }
    cout << "  [!] Khong tim thay hoa don [" << id << "].\n";
}

// ── Thống kê ─────────────────────────────────────────────────
void SalesManager::printStatistics(bool isOwner) const {
    cout << "\n===== THONG KE DOANH THU & LOI NHUAN =====\n";
    double totalRev = 0, totalPro = 0;
    map<string, int> soldQty;  // productId -> so luong ban

    for (auto& inv : invoices) {
        totalRev += inv.totalRevenue();
        totalPro += inv.totalProfit();
        for (auto& it : inv.items)
            soldQty[it.productId] += it.quantity;
    }

    cout << fixed << setprecision(0);
    cout << "  Tong so hoa don : " << invoices.size() << "\n";
    if (isOwner) {
        cout << "  Tong doanh thu  : " << totalRev << " VND\n";
        cout << "  Tong loi nhuan  : " << totalPro << " VND\n";
    } else {
        cout << "  Tong doanh thu  : (an - chi Owner xem)\n";
    }
    cout << "\n  --- So luong da ban theo SP ---\n";
    cout << "  " << left << setw(12) << "Ma SP" << setw(8) << "SL ban\n";
    cout << "  " << string(22, '-') << "\n";

    // Sắp xếp giảm dần
    vector<pair<string,int>> sorted(soldQty.begin(), soldQty.end());
    sort(sorted.begin(), sorted.end(),
         [](auto& a, auto& b){ return a.second > b.second; });
    for (auto& kv : sorted)
        cout << "  " << left << setw(12) << kv.first << kv.second << "\n";
}

// ── Xuất file hóa đơn ────────────────────────────────────────
void SalesManager::exportSummary() const {
    string fname = "export_summary.txt";
    ofstream ofs(fname);
    if (!ofs) { cout << "  [!] Khong the tao file.\n"; return; }

    ofs << "===== TONG HOP HOA DON =====\n";
    ofs << left << setw(12) << "Ma HD"
        << setw(12) << "NV"
        << setw(20) << "Ngay&Gio"
        << "Tong tien\n";
    ofs << string(60, '-') << "\n";
    double grand = 0;
    for (auto& inv : invoices) {
        ofs << fixed << setprecision(0)
            << left << setw(12) << inv.id
            << setw(12) << inv.staffId
            << setw(20) << inv.datetime
            << inv.totalRevenue() << " VND\n";
        grand += inv.totalRevenue();
    }
    ofs << string(60, '-') << "\n";
    ofs << "TONG CONG: " << grand << " VND\n";
    cout << "  [v] Da xuat file: " << fname << "\n";
}

void SalesManager::exportDetailed() const {
    string fname = "export_detailed.txt";
    ofstream ofs(fname);
    if (!ofs) { cout << "  [!] Khong the tao file.\n"; return; }

    ofs << "===== HOA DON CHI TIET =====\n\n";
    for (auto& inv : invoices) {
        ofs << "HOA DON: " << inv.id << "\n";
        ofs << "Nhan vien: " << inv.staffId  << "\n";
        ofs << "Ngay&Gio : " << inv.datetime << "\n";
        ofs << left << setw(10) << "Ma SP"
            << setw(25) << "Ten SP"
            << setw(6)  << "SL"
            << setw(12) << "Don gia"
            << "Thanh tien\n";
        ofs << string(60, '-') << "\n";
        for (auto& it : inv.items) {
            ofs << fixed << setprecision(0)
                << left << setw(10) << it.productId
                << setw(25) << it.productName
                << setw(6)  << it.quantity
                << setw(12) << it.unitPrice
                << it.subtotal() << " VND\n";
        }
        ofs << "TONG: " << inv.totalRevenue() << " VND\n\n";
    }
    cout << "  [v] Da xuat file: " << fname << "\n";
}

// ── Menu bán hàng ─────────────────────────────────────────────
void SalesManager::menuSales(const string& staffId, bool isOwner) {
    while (true) {
        clearScreen();
        cout << "\n===== QUAN LI BAN HANG =====\n";
        cout << "  1. Tao hoa don moi\n";
        cout << "  2. Xem danh sach hoa don\n";
        cout << "  3. Xem chi tiet hoa don\n";
        cout << "  4. Thong ke doanh thu & loi nhuan\n";
        cout << "  5. Xuat file tong hop (File 1)\n";
        cout << "  6. Xuat file chi tiet (File 2)\n";
        cout << "  0. Quay lai\n  Chon: ";
        int ch; cin >> ch; cin.ignore();
        clearScreen();
        switch (ch) {
            case 1: createInvoice(staffId); break;
            case 2: listInvoices(); break;
            case 3: viewInvoice(); break;
            case 4: printStatistics(isOwner); break;
            case 5: exportSummary(); break;
            case 6: exportDetailed(); break;
            case 0: return;
            default: cout << "  [!] Lua chon khong hop le.\n";
        }
        pauseScreen();
    }
}
