#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <limits>
#ifdef _WIN32
  #include <windows.h>
#else
  #include <cstdlib>
#endif

// ── Tiện ích chuỗi ───────────────────────────────────────────
string toLower(const string& s) {
    string r = s;
    transform(r.begin(), r.end(), r.begin(),
              [](unsigned char c){ return tolower(c); });
    return r;
}

string trim(const string& s) {
    size_t l = s.find_first_not_of(" \t\r\n");
    size_t r = s.find_last_not_of (" \t\r\n");
    return (l == string::npos) ? "" : s.substr(l, r - l + 1);
}

bool containsIgnoreCase(const string& haystack, const string& needle) {
    return toLower(haystack).find(toLower(needle)) != string::npos;
}

// ── Ngày giờ hiện tại ────────────────────────────────────────
string getCurrentDatetime() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    ostringstream oss;
    oss << setfill('0')
        << setw(2) << t->tm_mday << "/"
        << setw(2) << (t->tm_mon + 1) << "/"
        << (t->tm_year + 1900) << " "
        << setw(2) << t->tm_hour << ":"
        << setw(2) << t->tm_min  << ":"
        << setw(2) << t->tm_sec;
    return oss.str();
}

// ── Tạo ID ───────────────────────────────────────────────────
string generateId(const string& prefix, int counter) {
    ostringstream oss;
    oss << prefix << setw(4) << setfill('0') << counter;
    return oss.str();
}

// ── Nhập có kiểm tra ─────────────────────────────────────────
int inputInt(const string& prompt, int minVal, int maxVal) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= minVal && val <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Gia tri khong hop le. Vui long nhap lai.\n";
    }
}

double inputDouble(const string& prompt, double minVal) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= minVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Gia tri khong hop le. Vui long nhap lai.\n";
    }
}

string inputNonEmpty(const string& prompt) {
    string val;
    while (true) {
        cout << prompt;
        getline(cin, val);
        val = trim(val);
        if (!val.empty()) return val;
        cout << "  [!] Khong duoc de trong. Vui long nhap lai.\n";
    }
}

// ── Pause / Clear ─────────────────────────────────────────────
void pauseScreen() {
    cout << "\n  [Nhan Enter de tiep tuc...]";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ── File I/O ─────────────────────────────────────────────────
vector<string> readLines(const string& filename) {
    vector<string> lines;
    ifstream ifs(filename);
    if (!ifs.is_open()) return lines;
    string line;
    while (getline(ifs, line))
        if (!trim(line).empty())
            lines.push_back(line);
    return lines;
}

bool writeLines(const string& filename, const vector<string>& lines) {
    ofstream ofs(filename, ios::trunc);
    if (!ofs.is_open()) return false;
    for (auto& l : lines) ofs << l << "\n";
    return true;
}

bool appendLine(const string& filename, const string& line) {
    ofstream ofs(filename, ios::app);
    if (!ofs.is_open()) return false;
    ofs << line << "\n";
    return true;
}
