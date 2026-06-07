#include "Account.h"
#include <sstream>
#include <iomanip>

string roleToStr(Role r) {
    return (r == OWNER) ? "OWNER" : "STAFF";
}

Role strToRole(const string& s) {
    return (s == "OWNER") ? OWNER : STAFF;
}

// DJB2 hash – đủ dùng cho mục đích học tập
string hashPassword(const string& pwd) {
    unsigned long hash = 5381;
    for (char c : pwd)
        hash = ((hash << 5) + hash) + (unsigned char)c;
    ostringstream oss;
    oss << hex << setw(16) << setfill('0') << hash;
    return oss.str();
}

string Account::serialize() const {
    return username + "|" + passwordHash + "|" + roleToStr(role);
}

Account Account::deserialize(const string& line) {
    Account acc;
    istringstream iss(line);
    string tok;
    int idx = 0;
    while (getline(iss, tok, '|')) {
        switch (idx++) {
            case 0: acc.username     = tok; break;
            case 1: acc.passwordHash = tok; break;
            case 2: acc.role         = strToRole(tok); break;
        }
    }
    return acc;
}
