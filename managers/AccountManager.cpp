#include "AccountManager.h"
#include "../utils/Utils.h"
#include <iostream>
#include <iomanip>

AccountManager::AccountManager(const string& filename)
    : dataFile(filename), currentIdx(-1) {
    loadFromFile();
    // Nếu file trống, tạo tài khoản Owner mặc định
    if (accounts.empty()) {
        accounts.emplace_back("admin", hashPassword("admin123"), OWNER);
        saveToFile();
        cout << "  [i] Tao tai khoan mac dinh: admin / admin123\n";
    }
}

// ── File I/O ─────────────────────────────────────────────────
void AccountManager::loadFromFile() {
    accounts.clear();
    for (auto& line : readLines(dataFile))
        accounts.push_back(Account::deserialize(line));
}

void AccountManager::saveToFile() const {
    vector<string> lines;
    for (auto& a : accounts) lines.push_back(a.serialize());
    writeLines(dataFile, lines);
}

int AccountManager::findAccount(const string& username) const {
    for (int i = 0; i < (int)accounts.size(); ++i)
        if (accounts[i].username == username) return i;
    return -1;
}

// ── Đăng nhập / Đăng xuất ────────────────────────────────────
bool AccountManager::login(const string& username, const string& password) {
    int idx = findAccount(username);
    if (idx == -1) return false;
    if (accounts[idx].passwordHash != hashPassword(password)) return false;
    currentIdx = idx;
    return true;
}

void AccountManager::logout() { currentIdx = -1; }
bool AccountManager::isLoggedIn()  const { return currentIdx != -1; }
const Account* AccountManager::currentAccount() const {
    return isLoggedIn() ? &accounts[currentIdx] : nullptr;
}
bool AccountManager::isOwner() const {
    return isLoggedIn() && accounts[currentIdx].role == OWNER;
}

// ── Đổi mật khẩu ─────────────────────────────────────────────
void AccountManager::changePassword() {
    if (!isLoggedIn()) { cout << "  [!] Chua dang nhap.\n"; return; }
    cout << "\n--- DOI MAT KHAU ---\n";
    string oldPwd = inputNonEmpty("  Mat khau cu   : ");
    if (accounts[currentIdx].passwordHash != hashPassword(oldPwd)) {
        cout << "  [!] Mat khau cu khong dung.\n"; return;
    }
    string newPwd  = inputNonEmpty("  Mat khau moi  : ");
    string confirm = inputNonEmpty("  Xac nhan lai  : ");
    if (newPwd != confirm) { cout << "  [!] Xac nhan khong khop.\n"; return; }
    accounts[currentIdx].passwordHash = hashPassword(newPwd);
    saveToFile();
    cout << "  [v] Doi mat khau thanh cong.\n";
}

// ── Thêm tài khoản (Owner) ────────────────────────────────────
void AccountManager::addAccount() {
    if (!isOwner()) { cout << "  [!] Khong co quyen.\n"; return; }
    cout << "\n--- THEM TAI KHOAN ---\n";
    string uname = inputNonEmpty("  Ten dang nhap : ");
    if (findAccount(uname) != -1) { cout << "  [!] Ten da ton tai.\n"; return; }
    string pwd   = inputNonEmpty("  Mat khau      : ");
    cout << "  Quyen (1=Owner, 2=Staff) [2]: ";
    int ch = 2;
    cin >> ch; cin.ignore();
    Role r = (ch == 1) ? OWNER : STAFF;
    accounts.emplace_back(uname, hashPassword(pwd), r);
    saveToFile();
    cout << "  [v] Them tai khoan thanh cong.\n";
}

// ── Xóa tài khoản (Owner) ─────────────────────────────────────
void AccountManager::removeAccount() {
    if (!isOwner()) { cout << "  [!] Khong co quyen.\n"; return; }
    cout << "\n--- XOA TAI KHOAN ---\n";
    listAccounts();
    string uname = inputNonEmpty("  Ten can xoa   : ");
    if (uname == accounts[currentIdx].username) {
        cout << "  [!] Khong the xoa chinh minh.\n"; return;
    }
    int idx = findAccount(uname);
    if (idx == -1) { cout << "  [!] Khong tim thay.\n"; return; }
    accounts.erase(accounts.begin() + idx);
    saveToFile();
    cout << "  [v] Xoa thanh cong.\n";
}

// ── Danh sách tài khoản ───────────────────────────────────────
void AccountManager::listAccounts() const {
    cout << "\n  " << left << setw(20) << "Ten dang nhap" << "Quyen\n";
    cout << "  " << string(30, '-') << "\n";
    for (auto& a : accounts)
        cout << "  " << left << setw(20) << a.username << roleToStr(a.role) << "\n";
}

// ── Menu ──────────────────────────────────────────────────────
void AccountManager::menuAccount() {
    while (true) {
        clearScreen();
        cout << "\n===== QUAN LI TAI KHOAN =====\n";
        cout << "  Nguoi dung: " << accounts[currentIdx].username
             << " [" << roleToStr(accounts[currentIdx].role) << "]\n\n";
        cout << "  1. Doi mat khau\n";
        if (isOwner()) {
            cout << "  2. Them tai khoan\n";
            cout << "  3. Xoa tai khoan\n";
            cout << "  4. Danh sach tai khoan\n";
        }
        cout << "  0. Quay lai\n";
        cout << "  Chon: ";
        int ch;
        cin >> ch; cin.ignore();
        clearScreen();
        switch (ch) {
            case 1: changePassword(); break;
            case 2: if (isOwner()) addAccount(); break;
            case 3: if (isOwner()) removeAccount(); break;
            case 4: if (isOwner()) listAccounts(); break;
            case 0: return;
            default: cout << "  [!] Lua chon khong hop le.\n";
        }
        pauseScreen();
    }
}
