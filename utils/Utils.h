#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// ── Tiện ích chuỗi ───────────────────────────────────────────
string toLower(const string& s);
string trim(const string& s);
bool   containsIgnoreCase(const string& haystack, const string& needle);

// ── Lấy ngày giờ hiện tại ────────────────────────────────────
string getCurrentDatetime();

// ── Tạo ID tự động ───────────────────────────────────────────
string generateId(const string& prefix, int counter);

// ── Nhập có kiểm tra ─────────────────────────────────────────
int    inputInt(const string& prompt, int minVal = 0, int maxVal = 1e9);
double inputDouble(const string& prompt, double minVal = 0);
string inputNonEmpty(const string& prompt);

// ── Pause / Clear ─────────────────────────────────────────────
void   pauseScreen();
void   clearScreen();

// ── Đọc/ghi file văn bản ─────────────────────────────────────
vector<string> readLines(const string& filename);
bool           writeLines(const string& filename, const vector<string>& lines);
bool           appendLine(const string& filename, const string& line);
