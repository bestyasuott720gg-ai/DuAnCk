#include "Product.h"
#include <sstream>
#include <iomanip>

// ── Helper ──────────────────────────────────────────────────
string productTypeToStr(ProductType t) {
    switch (t) {
        case CLOTHING:    return "CLOTHING";
        case RACKET:      return "RACKET";
        case ACCESSORY:   return "ACCESSORY";
        case SHUTTLECOCK: return "SHUTTLECOCK";
    }
    return "UNKNOWN";
}

ProductType strToProductType(const string& s) {
    if (s == "CLOTHING")    return CLOTHING;
    if (s == "RACKET")      return RACKET;
    if (s == "ACCESSORY")   return ACCESSORY;
    return SHUTTLECOCK;
}

// ── Constructor ─────────────────────────────────────────────
Product::Product()
    : quantity(0), salePrice(0), importPrice(0), type(ACCESSORY) {}

// ── Display ─────────────────────────────────────────────────
void Product::display() const {
    cout << "========================================\n";
    cout << "  Ma SP   : " << id   << "\n";
    cout << "  Ten     : " << name << "\n";
    cout << "  Hang    : " << brand << "\n";
    cout << "  Loai    : " << productTypeToStr(type) << "\n";
    cout << "  So luong: " << quantity << "\n";
    cout << fixed << setprecision(0);
    cout << "  Gia ban : " << salePrice   << " VND\n";
    cout << "  Gia nhap: " << importPrice << " VND\n";
    if (type == CLOTHING) {
        cout << "  Mau     : " << color    << "\n";
        cout << "  Kich co : " << size     << "\n";
        cout << "  Chat lieu: " << material << "\n";
    } else if (type == RACKET) {
        cout << "  Mau     : " << color      << "\n";
        cout << "  Thong so: " << specs      << "\n";
        cout << "  Do kho  : " << difficulty << "\n";
    }
    cout << "========================================\n";
}

void Product::displayShort() const {
    cout << fixed << setprecision(0);
    cout << left
         << setw(10) << id
         << setw(25) << name
         << setw(15) << brand
         << setw(6)  << quantity
         << setw(12) << salePrice
         << productTypeToStr(type) << "\n";
}

// ── Serialize ────────────────────────────────────────────────
// Format: field1|field2|...|field14
// (dùng '|' vì tên/hãng có thể chứa dấu phẩy)
string Product::serialize() const {
    ostringstream oss;
    oss << id           << "|"
        << name         << "|"
        << brand        << "|"
        << quantity     << "|"
        << fixed << setprecision(2) << salePrice  << "|"
        << importPrice  << "|"
        << productTypeToStr(type) << "|"
        << color        << "|"
        << size         << "|"
        << material     << "|"
        << specs        << "|"
        << difficulty;
    return oss.str();
}

Product Product::deserialize(const string& line) {
    Product p;
    istringstream iss(line);
    string tok;
    int idx = 0;
    while (getline(iss, tok, '|')) {
        switch (idx++) {
            case 0:  p.id          = tok; break;
            case 1:  p.name        = tok; break;
            case 2:  p.brand       = tok; break;
            case 3:  p.quantity    = stoi(tok); break;
            case 4:  p.salePrice   = stod(tok); break;
            case 5:  p.importPrice = stod(tok); break;
            case 6:  p.type        = strToProductType(tok); break;
            case 7:  p.color       = tok; break;
            case 8:  p.size        = tok; break;
            case 9:  p.material    = tok; break;
            case 10: p.specs       = tok; break;
            case 11: p.difficulty  = tok; break;
        }
    }
    return p;
}
