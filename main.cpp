/*
 * ============================================================
 *  QUAN LI SHOP CAU LONG  –  PBL Project (Year 1)
 *  Build:  g++ -std=c++17 -o shop main.cpp
 *               models/Product.cpp models/Invoice.cpp models/Account.cpp
 *               managers/AccountManager.cpp managers/ProductManager.cpp
 *               managers/SalesManager.cpp
 *               utils/Utils.cpp
 * ============================================================
 */
#include <iostream>
#include <string>

#include "models/Account.h"
#include "managers/AccountManager.h"
#include "managers/ProductManager.h"
#include "managers/SalesManager.h"
#include "utils/Utils.h"

using namespace std;

// ── Màn hình đăng nhập ───────────────────────────────────────
bool doLogin(AccountManager& am) {
    clearScreen();
    cout << R"(
  =============================================
    QUAN LI SHOP CAU LONG
  =============================================
)" << "\n";
    cout << "  Ten dang nhap: ";
    string user; getline(cin, user);
    cout << "  Mat khau     : ";
    string pwd; getline(cin, pwd);
    if (am.login(user, pwd)) {
        cout << "\n  [v] Dang nhap thanh cong. Xin chao, " << user << "!\n";
        pauseScreen();
        return true;
    }
    cout << "\n  [!] Sai ten dang nhap hoac mat khau.\n";
    pauseScreen();
    return false;
}

// ── Menu chính ────────────────────────────────────────────────
void mainMenu(AccountManager& am, ProductManager& pm, SalesManager& sm) {
    while (true) {
        clearScreen();
        auto* acc = am.currentAccount();
        bool isOwner = am.isOwner();

        cout << "\n===== MENU CHINH =====\n";
        cout << "  Nguoi dung: " << acc->username
             << "  [" << roleToStr(acc->role) << "]\n\n";

        cout << "  1. Thong tin san pham\n";
        if (isOwner)
            cout << "  2. Quan li thong tin hang hoa\n";
        cout << "  3. Quan li ban hang\n";
        cout << "  4. Chuc nang tien ich\n";
        cout << "  5. Quan li tai khoan\n";
        cout << "  6. Canh bao hang sap het\n";
        cout << "  0. Dang xuat\n";
        cout << "  Chon: ";
        int ch; cin >> ch; cin.ignore();
        clearScreen();

        switch (ch) {
            case 1: pm.menuProductInfo(isOwner);     break;
            case 2:
                if (isOwner) pm.menuManageInfo(isOwner);
                else cout << "  [!] Khong co quyen.\n";
                break;
            case 3: sm.menuSales(acc->username, isOwner); break;
            case 4: pm.menuUtility();                break;
            case 5: am.menuAccount();                break;
            case 6: pm.checkLowStock(); pauseScreen(); break;
            case 0:
                am.logout();
                cout << "  Da dang xuat.\n";
                return;
            default: cout << "  [!] Lua chon khong hop le.\n"; pauseScreen();
        }
    }
}

// ── Hàm main ─────────────────────────────────────────────────
int main() {
    // Tên file dữ liệu
    const string ACCOUNT_FILE = "data_accounts.txt";
    const string PRODUCT_FILE = "data_products.txt";
    const string INVOICE_FILE = "data_invoices.txt";

    AccountManager am(ACCOUNT_FILE);
    ProductManager pm(PRODUCT_FILE);
    SalesManager   sm(INVOICE_FILE, pm);

    while (true) {
        clearScreen();
        cout << "\n===========================\n";
        cout << "   SHOP CAU LONG MANAGER\n";
        cout << "===========================\n";
        cout << "  1. Dang nhap\n";
        cout << "  0. Thoat\n";
        cout << "  Chon: ";
        int ch; cin >> ch; cin.ignore();

        if (ch == 0) break;
        if (ch == 1) {
            if (doLogin(am))
                mainMenu(am, pm, sm);
        }
    }

    cout << "\n  Cam on! Hen gap lai.\n\n";
    return 0;
}
