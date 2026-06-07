#include "ProductManager.h"
#include "../utils/Utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

ProductManager::ProductManager(const string& filename)
    : dataFile(filename), idCounter(1) {
    loadFromFile();
}

// ── File I/O ─────────────────────────────────────────────────
void ProductManager::loadFromFile() {
    products.clear(); idCounter = 1;
    for (auto& line : readLines(dataFile)) {
        products.push_back(Product::deserialize(line));
        idCounter++;
    }
}

void ProductManager::saveToFile() const {
    vector<string> lines;
    for (auto& p : products) lines.push_back(p.serialize());
    writeLines(dataFile, lines);
}

bool ProductManager::idExists(const string& id) const {
    for (auto& p : products) if (p.id == id) return true;
    return false;
}

// ── Nhập thông tin sản phẩm ──────────────────────────────────
void ProductManager::inputProductFields(Product& p, bool isNew) {
    if (isNew) {
        cout << "  Loai SP (1=QuanAo 2=Vot 3=PhuKien 4=Cau): ";
        int t; cin >> t; cin.ignore();
        p.type = (t==1) ? CLOTHING : (t==2) ? RACKET :
                 (t==3) ? ACCESSORY : SHUTTLECOCK;
        p.id = generateId("SP", idCounter++);
        cout << "  Ma SP tu dong: " << p.id << "\n";
    }
    p.name   = inputNonEmpty("  Ten SP        : ");
    p.brand  = inputNonEmpty("  Hang          : ");
    p.quantity    = inputInt   ("  So luong      : ", 0);
    p.salePrice   = inputDouble("  Gia ban (VND) : ", 0);
    p.importPrice = inputDouble("  Gia nhap (VND): ", 0);

    if (p.type == CLOTHING) {
        p.color    = inputNonEmpty("  Mau           : ");
        p.size     = inputNonEmpty("  Kich co (S/M/L/XL): ");
        p.material = inputNonEmpty("  Chat lieu     : ");
    } else if (p.type == RACKET) {
        p.color      = inputNonEmpty("  Mau           : ");
        p.specs      = inputNonEmpty("  Thong so      : ");
        p.difficulty = inputNonEmpty("  Do kho (Beginner/Intermediate/Advanced): ");
    }
}

// ── Thêm ─────────────────────────────────────────────────────
void ProductManager::addProduct() {
    cout << "\n--- THEM SAN PHAM ---\n";
    Product p;
    inputProductFields(p, true);
    products.push_back(p);
    saveToFile();
    cout << "  [v] Them san pham [" << p.id << "] thanh cong.\n";
}

// ── Xóa ──────────────────────────────────────────────────────
void ProductManager::removeProduct() {
    cout << "\n--- XOA SAN PHAM ---\n";
    string id = inputNonEmpty("  Ma SP can xoa : ");
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->id == id) {
            products.erase(it);
            saveToFile();
            cout << "  [v] Xoa thanh cong.\n";
            return;
        }
    }
    cout << "  [!] Khong tim thay ma [" << id << "].\n";
}

// ── Cập nhật ─────────────────────────────────────────────────
void ProductManager::updateProduct() {
    cout << "\n--- CAP NHAT SAN PHAM ---\n";
    string id = inputNonEmpty("  Ma SP can sua : ");
    for (auto& p : products) {
        if (p.id == id) {
            p.display();
            cout << "  Nhap thong tin moi:\n";
            inputProductFields(p, false);
            saveToFile();
            cout << "  [v] Cap nhat thanh cong.\n";
            return;
        }
    }
    cout << "  [!] Khong tim thay ma [" << id << "].\n";
}

// ── Hiển thị ─────────────────────────────────────────────────
void ProductManager::printHeader() const {
    cout << "\n  " << left
         << setw(10) << "Ma SP"
         << setw(25) << "Ten"
         << setw(15) << "Hang"
         << setw(6)  << "SL"
         << setw(12) << "Gia ban"
         << "Loai\n";
    cout << "  " << string(78, '-') << "\n";
}

void ProductManager::listAll() const {
    cout << "\n===== DANH SACH SAN PHAM (" << products.size() << " SP) =====\n";
    printHeader();
    for (auto& p : products) { cout << "  "; p.displayShort(); }
}

void ProductManager::listSorted() const {
    vector<Product> sorted = products;
    sort(sorted.begin(), sorted.end(),
         [](const Product& a, const Product& b){
             return toLower(a.name) < toLower(b.name); });
    cout << "\n===== SAN PHAM (A-Z) =====\n";
    printHeader();
    for (auto& p : sorted) { cout << "  "; p.displayShort(); }
}

// ── Tìm kiếm ─────────────────────────────────────────────────
Product* ProductManager::findById(const string& id) {
    for (auto& p : products) if (p.id == id) return &p;
    return nullptr;
}

const Product* ProductManager::findById(const string& id) const {
    for (auto& p : products) if (p.id == id) return &p;
    return nullptr;
}

vector<Product*> ProductManager::searchByName(const string& keyword) {
    vector<Product*> res;
    for (auto& p : products)
        if (containsIgnoreCase(p.name, keyword) ||
            containsIgnoreCase(p.id,   keyword))
            res.push_back(&p);
    return res;
}

vector<Product*> ProductManager::searchByBrand(const string& brand) {
    vector<Product*> res;
    for (auto& p : products)
        if (containsIgnoreCase(p.brand, brand)) res.push_back(&p);
    return res;
}

vector<Product*> ProductManager::searchByPriceRange(double minP, double maxP) {
    vector<Product*> res;
    for (auto& p : products)
        if (p.salePrice >= minP && p.salePrice <= maxP) res.push_back(&p);
    return res;
}

// ── Hàng sắp hết ─────────────────────────────────────────────
void ProductManager::checkLowStock(int threshold) const {
    cout << "\n===== CANH BAO HANG SAP HET (< " << threshold << ") =====\n";
    bool found = false;
    printHeader();
    for (auto& p : products) {
        if (p.quantity < threshold) {
            cout << "  "; p.displayShort();
            found = true;
        }
    }
    if (!found) cout << "  [v] Tat ca san pham du hang.\n";
}

// ── Giảm tồn kho ─────────────────────────────────────────────
bool ProductManager::decreaseStock(const string& id, int qty) {
    for (auto& p : products) {
        if (p.id == id) {
            if (p.quantity < qty) return false;
            p.quantity -= qty;
            saveToFile();
            return true;
        }
    }
    return false;
}

// ── Menu thông tin sản phẩm ───────────────────────────────────
void ProductManager::menuProductInfo(bool isOwner) {
    while (true) {
        clearScreen();
        cout << "\n===== THONG TIN SAN PHAM =====\n";
        cout << "  1. Xem danh sach san pham\n";
        cout << "  2. Xem chi tiet san pham\n";
        if (isOwner) {
            cout << "  3. Them san pham\n";
            cout << "  4. Xoa san pham\n";
            cout << "  5. Cap nhat san pham\n";
        }
        cout << "  0. Quay lai\n  Chon: ";
        int ch; cin >> ch; cin.ignore();
        clearScreen();
        switch (ch) {
            case 1: listAll(); break;
            case 2: {
                string id = inputNonEmpty("  Ma SP: ");
                auto* p = findById(id);
                if (p) p->display();
                else cout << "  [!] Khong tim thay.\n";
                break;
            }
            case 3: if (isOwner) addProduct(); break;
            case 4: if (isOwner) removeProduct(); break;
            case 5: if (isOwner) updateProduct(); break;
            case 0: return;
            default: cout << "  [!] Lua chon khong hop le.\n";
        }
        pauseScreen();
    }
}

// ── Menu quản lý thông tin ────────────────────────────────────
void ProductManager::menuManageInfo(bool isOwner) {
    if (!isOwner) { cout << "  [!] Khong co quyen.\n"; return; }
    while (true) {
        clearScreen();
        cout << "\n===== QUAN LI THONG TIN HANG HOA =====\n";
        cout << "  1. Them san pham\n";
        cout << "  2. Xoa san pham\n";
        cout << "  3. Cap nhat san pham\n";
        cout << "  4. Sap xep A-Z\n";
        cout << "  0. Quay lai\n  Chon: ";
        int ch; cin >> ch; cin.ignore();
        clearScreen();
        switch (ch) {
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: updateProduct(); break;
            case 4: listSorted(); break;
            case 0: return;
            default: cout << "  [!] Lua chon khong hop le.\n";
        }
        pauseScreen();
    }
}

// ── Menu tiện ích ─────────────────────────────────────────────
void ProductManager::menuUtility() {
    while (true) {
        clearScreen();
        cout << "\n===== CHUC NANG TIEN ICH =====\n";
        cout << "  1. Tim kiem theo ten/ma SP\n";
        cout << "  2. Tim kiem theo hang\n";
        cout << "  3. Tim kiem theo khoang gia\n";
        cout << "  4. Canh bao hang sap het\n";
        cout << "  0. Quay lai\n  Chon: ";
        int ch; cin >> ch; cin.ignore();
        clearScreen();
        switch (ch) {
            case 1: {
                string kw = inputNonEmpty("  Tu khoa: ");
                auto res = searchByName(kw);
                if (res.empty()) { cout << "  Khong tim thay.\n"; break; }
                printHeader();
                for (auto* p : res) { cout << "  "; p->displayShort(); }
                break;
            }
            case 2: {
                string br = inputNonEmpty("  Hang: ");
                auto res = searchByBrand(br);
                if (res.empty()) { cout << "  Khong tim thay.\n"; break; }
                printHeader();
                for (auto* p : res) { cout << "  "; p->displayShort(); }
                break;
            }
            case 3: {
                double mn = inputDouble("  Gia tu (VND): ");
                double mx = inputDouble("  Gia den (VND): ", mn);
                auto res = searchByPriceRange(mn, mx);
                if (res.empty()) { cout << "  Khong co SP trong khoang gia.\n"; break; }
                printHeader();
                for (auto* p : res) { cout << "  "; p->displayShort(); }
                break;
            }
            case 4: checkLowStock(); break;
            case 0: return;
            default: cout << "  [!] Lua chon khong hop le.\n";
        }
        pauseScreen();
    }
}
