#pragma once
#include "../models/Account.h"
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  Quản lý tài khoản
// ============================================================
class AccountManager {
public:
    AccountManager(const string& filename);

    bool        login(const string& username, const string& password);
    void        logout();
    bool        isLoggedIn() const;
    const Account* currentAccount() const;
    bool        isOwner() const;

    void        changePassword();
    void        addAccount();        // Chỉ Owner
    void        removeAccount();     // Chỉ Owner
    void        listAccounts() const;

    void        menuAccount();

private:
    string           dataFile;
    vector<Account>  accounts;
    int              currentIdx;   // -1 = chưa đăng nhập

    void loadFromFile();
    void saveToFile() const;
    int  findAccount(const string& username) const;
};
