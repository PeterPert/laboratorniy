#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ofstream file("products.csv");
    if (!file.is_open()) {
        cout << "Ошибка создания файла!" << endl;
        return 1;
    }
    
    // Заголовки
    file << "id,name,category,price,quantity" << endl;
    
    int productCount;
    cout << "Сколько товаров добавить? ";
    cin >> productCount;
    cin.ignore(); 
    for (int i = 1; i <= productCount; i++) {
        cout << "\nТовар #" << i << ":" << endl;
        string name, category;
        double price;
        int quantity;
        cout << "Название: ";
        getline(cin, name);
        cout << "Категория: ";
        getline(cin, category);
        cout << "Цена: ";
        cin >> price;
        cout << "Количество: ";
        cin >> quantity;
        cin.ignore(); 
        file << i << "," << name << "," << category << "," 
             << fixed << setprecision(2) << price << "," << quantity << endl;
    }
    
    file.close();
    cout << "\nДанные сохранены в products.csv" << endl;
    
    return 0;
}