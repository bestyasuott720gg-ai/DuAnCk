#pragma once
#include "../models/Invoice.h"
#include "ProductManager.h"
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  Quản lý bán hàng
// ============================================================
class SalesManager {
public:
    SalesManager(const string& invoiceFile, ProductManager& pm);

    void createInvoice(const string& staffId);
    void listInvoices() const;
    void viewInvoice() const;

    // Thống kê
    void printStatistics(bool isOwner) const;

    // Xuất file
    void exportSummary()  const;   // File 1: tổng hợp
    void exportDetailed() const;   // File 2: chi tiết

    void menuSales(const string& staffId, bool isOwner);

private:
    string            dataFile;
    vector<Invoice>   invoices;
    ProductManager&   pm;
    int               idCounter;

    void loadFromFile();
    void saveToFile() const;
};
