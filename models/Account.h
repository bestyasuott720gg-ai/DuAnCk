#pragma once
#include <string>
using namespace std;

enum Role { OWNER, STAFF };

string roleToStr(Role r);
Role   strToRole(const string& s);

struct Account {
    string username;
    string passwordHash;  // SHA-256 đơn giản hoặc hash tự implement
    Role   role;

    Account() : role(STAFF) {}
    Account(const string& u, const string& ph, Role r)
        : username(u), passwordHash(ph), role(r) {}

    string serialize()   const;
    static Account deserialize(const string& line);
};

// Hàm băm mật khẩu đơn giản (dùng DJB2)
string hashPassword(const string& pwd);
