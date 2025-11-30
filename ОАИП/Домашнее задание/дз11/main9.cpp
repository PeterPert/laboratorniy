#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Product {
    int id;
    string name;
    string category;
    double price;
    int quantity;
};

int main() {
    vector<Product> products;
    ifstream file("products.csv");
    string line;
    getline(file, line); // пропускаем заголовок
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Product p;
        getline(ss, token, ','); p.id = stoi(token);
        getline(ss, p.name, ',');
        getline(ss, p.category, ',');
        getline(ss, token, ','); p.price = stod(token);
        getline(ss, token); p.quantity = stoi(token);
        products.push_back(p);
    }
    file.close();

    cout << "Всего товаров: " << products.size() << endl;
    cout << "\nВыберите критерий сортировки:\n";
    cout << "1 - Цена (по возрастанию)\n";
    cout << "2 - Цена (по убыванию)\n";
    cout << "3 - Название (А-Я)\n";
    cout << "4 - Количество (по убыванию)\n";
    
    int choice;
    cin >> choice;
    
    // Лямбда-функции для сортировки
    switch (choice) {
        case 1: {
            auto price_asc = [](const Product& a, const Product& b) {
                return a.price < b.price;
            };
            sort(products.begin(), products.end(), price_asc);
            cout << "Сортировка: цена по возрастанию\n";
            break;
        }
        
        case 2: {
            auto price_desc = [](const Product& a, const Product& b) {
                return a.price > b.price;
            };
            sort(products.begin(), products.end(), price_desc);
            cout << "Сортировка: цена по убыванию\n";
            break;
        }
        
        case 3: {
            auto name_asc = [](const Product& a, const Product& b) {
                return a.name < b.name;
            };
            sort(products.begin(), products.end(), name_asc);
            cout << "Сортировка: название А-Я\n";
            break;
        }
        
        case 4: {
            auto quantity_desc = [](const Product& a, const Product& b) {
                return a.quantity > b.quantity;
            };
            sort(products.begin(), products.end(), quantity_desc);
            cout << "Сортировка: количество по убыванию\n";
            break;
        }
        default:
            cout << "Неверный выбор!\n";
            return 1;
    }
    ofstream infile("sorted_products.csv");
    infile << "id,name,category,price,quantity" << endl;
    
    for (const auto& p : products) {
        infile << p.id << "," << p.name << "," << p.category << ","
             << fixed << setprecision(2) << p.price << "," << p.quantity << endl;
    }
    infile.close();
    cout << "\nОтсортированные данные сохранены в sorted_products.csv" << endl;
    return 0;
}