#pragma once
#include "../models/Product.h"
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  Quản lý sản phẩm
// ============================================================
class ProductManager {
public:
    ProductManager(const string& filename);

    // CRUD
    void addProduct();
    void removeProduct();
    void updateProduct();
    void listAll() const;
    void listSorted() const;   // Sắp xếp A→Z

    // Tra cứu
    Product* findById(const string& id);
    const Product* findById(const string& id) const;
    vector<Product*> searchByName(const string& keyword);
    vector<Product*> searchByBrand(const string& brand);
    vector<Product*> searchByPriceRange(double minP, double maxP);

    // Cảnh báo hàng sắp hết
    void checkLowStock(int threshold = 5) const;

    // Cập nhật số lượng sau bán
    bool decreaseStock(const string& id, int qty);

    void menuProductInfo(bool isOwner);
    void menuManageInfo(bool isOwner);
    void menuUtility();

    // Accessor
    const vector<Product>& getProducts() const { return products; }

private:
    string          dataFile;
    vector<Product> products;
    int             idCounter;

    void loadFromFile();
    void saveToFile() const;
    bool idExists(const string& id) const;
    void inputProductFields(Product& p, bool isNew = true);
    void printHeader() const;
};
