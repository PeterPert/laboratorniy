#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Product {
    int id;
    string name;
    string category;
    double price;
    int quantity;
};

int main() {
    // Чтение данных
    vector<Product> products;
    ifstream file("products.csv");
    string line;
    
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Product p;
        
        getline(ss, token, ','); p.id = stoi(token);
        getline(ss, p.name, ',');
        getline(ss, p.category, ',');
        getline(ss, token, ','); p.price = stod(token); // stod - потому что double а не int
        getline(ss, token); p.quantity = stoi(token);
        
        products.push_back(p);
    }
    file.close();
    
    // Лямбда-функции для разных фильтров
    auto expensive_filter = [](const Product& p) { return p.price > 5000; };
    auto electronics_filter = [](const Product& p) { return p.category == "Электроника"; };
    auto available_filter = [](const Product& p) { return p.quantity > 10; };
    auto cheap_filter = [](const Product& p) { return p.price < 1000; };
    
    // Применяем фильтры
    vector<Product> expensive, electronics, available, cheap;
    
    copy_if(products.begin(), products.end(), back_inserter(expensive), expensive_filter);
    copy_if(products.begin(), products.end(), back_inserter(electronics), electronics_filter);
    copy_if(products.begin(), products.end(), back_inserter(available), available_filter);
    copy_if(products.begin(), products.end(), back_inserter(cheap), cheap_filter);
    
    // Сохраняем результаты
    auto saveFiltered = [](const vector<Product>& filtered, const string& filename) {
        ofstream file(filename);
        file << "id,name,category,price,quantity" << endl;
        for (const auto& p : filtered) {
            file << p.id << "," << p.name << "," << p.category << ","
                 << fixed << p.price << "," << p.quantity << endl;
        }
        file.close();
    };
    
    saveFiltered(expensive, "expensive_products.csv");
    saveFiltered(electronics, "electronics_products.csv");
    saveFiltered(available, "available_products.csv");
    saveFiltered(cheap, "cheap_products.csv");
    
    cout << "Статистика фильтрации:\n";
    cout << "Товары дороже 5000 руб.: " << expensive.size() << endl;
    cout << "Электроника: " << electronics.size() << endl;
    cout << "В наличии (>10 шт.): " << available.size() << endl;
    cout << "Дешевые товары (<1000 руб.): " << cheap.size() << endl;
    
    return 0;
}