#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
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
    
    if (!file.is_open()) {
        cout << "Ошибка открытия файла products.csv!" << endl;
        return 1;
    }
    
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Product product;
        getline(ss, token, ',');
        product.id = stoi(token);
        getline(ss, product.name, ',');
        getline(ss, product.category, ',');
        getline(ss, token, ',');
        product.price = stod(token);
        getline(ss, token);
        product.quantity = stoi(token);
        products.push_back(product);
    }
    file.close();
    
    cout << left << setw(3) << "ID" << setw(25) << "Название" << setw(15) << "Категория" << setw(10) << "Цена" << setw(10) << "Кол-во" << endl;
    
    for (const auto& product : products) {
        cout << left << setw(3) << product.id 
             << setw(25) << product.name 
             << setw(15) << product.category
             << setw(10) << fixed << setprecision(2) << product.price
             << setw(10) << product.quantity << endl;
    }
    
    // Статистика
    int totalQuantity = 0;
    double totalValue = 0.0;
    Product mostExpensive = products[0];
    Product cheapest = products[0];
    
    for (const auto& product : products) {
        totalQuantity += product.quantity;
        totalValue += product.price * product.quantity;
        
        if (product.price > mostExpensive.price) {
            mostExpensive = product;
        }
        if (product.price < cheapest.price) {
            cheapest = product;
        }
    }
    
    cout << "\nСТАТИСТИКА:" << endl;
    cout << "Общее количество товаров на складе: " << totalQuantity << " шт." << endl;
    cout << "Суммарная стоимость всех товаров: " << fixed << setprecision(2) << totalValue << " руб." << endl;
    cout << "Самый дорогой товар: " << mostExpensive.name << " (" << mostExpensive.price << " руб.)" << endl;
    cout << "Самый дешевый товар: " << cheapest.name << " (" << cheapest.price << " руб.)" << endl;
    cout << "Количество позиций: " << products.size() << endl;
    return 0;
}