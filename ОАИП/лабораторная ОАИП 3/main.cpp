#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Product {
    string name;
    int quantity;
    double price;
};

// Функция для записи в output.txt
void writeToOutput(const string& message) {
    ofstream outFile("output.txt", ios::app);
    if (outFile.is_open()) {
        outFile << message << endl;
        outFile.close();
    }
}

// Функция для чтения всех товаров из файла
vector<Product> readProductsFromFile() {
    vector<Product> products;
    ifstream inFile("orders.txt");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        Product product;
        ss >> product.name >> product.quantity >> product.price;
        products.push_back(product);
    }
    inFile.close();
    return products;
}

// Функция сортировки 
void sortProducts() {
    vector<Product> products = readProductsFromFile();
    
    if (products.empty()) {
        cout << "Файл пуст или не существует" << endl;
        writeToOutput("Ошибка: Файл пуст или не существует");
        return;
    }
    
    int sortChoice;
    cout << "\n=== Критерии сортировки ===" << endl;
    cout << "1. По названию товара" << endl;
    cout << "2. По количеству единиц" << endl;
    cout << "3. По цене за единицу" << endl;
    cout << "Выберите критерий сортировки: ";
    cin >> sortChoice;
    int n = products.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            bool needSwap = false;
            
            switch (sortChoice) {
                case 1:
                    if (products[j].name > products[j + 1].name) {
                        needSwap = true;
                    }
                    break;
                case 2:
                    if (products[j].quantity > products[j + 1].quantity) {
                        needSwap = true;
                    }
                    break;
                case 3:
                    if (products[j].price > products[j + 1].price) {
                        needSwap = true;
                    }
                    break;
                default:
                    cout << "Неверный выбор. Сортировка отменена." << endl;
                    return;
            }
            // Если нужно поменять элементы местами
            if (needSwap) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    ofstream outputFile("orders.txt");
    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия файла для записи" << endl;
        writeToOutput("Ошибка открытия файла orders.txt для записи");
        return;
    }
    for (const auto& product : products) {
        outputFile << product.name << " " << product.quantity << " " << product.price << endl;
    }
    outputFile.close();
    
    string sortMessage;
    switch (sortChoice) {
        case 1:
            sortMessage = "Товары отсортированы по названию (алфавитный порядок)";
            break;
        case 2:
            sortMessage = "Товары отсортированы по количеству (по возрастанию)";
            break;
        case 3:
            sortMessage = "Товары отсортированы по цене (по возрастанию)";
            break;
    }
    cout << sortMessage << endl;
    // Записываем отсортированный список в output.txt
    writeToOutput("Отсортированный список товаров:");
    for (const auto& product : products) {
        string productInfo = product.name + " " + to_string(product.quantity) + " " + to_string(product.price);
        cout << productInfo << endl;
        writeToOutput(productInfo);
    }
}

void poisk(string per){
    ifstream inFile("orders.txt");
    string line;
    bool sost = false;
    do {
        getline(inFile, line);
        stringstream ss(line);
        string firstWord;
        ss >> firstWord; 
        if (firstWord == per){
            string result = firstWord + " ";
            string word;
            while (ss >> word){
                result += word + " ";
            } 
            cout << result << endl;
            writeToOutput("Найден товар: " + result);
            sost = true;
        }   
    }while(! line.empty());
    
    if (!sost){
        cout << "такого товара не найдено" << endl;
        writeToOutput("Товар не найден: " + per);
    }
}

void dobav(){
    ofstream outputFile("orders.txt", ios::app); 
    if (!outputFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл orders.txt для записи." << endl;
        writeToOutput("Ошибка: не удалось открыть файл orders.txt для записи");
        return;
    }
    
    string productName;
    int quantity;
    double price;
    cout << "Введите название товара: ";
    cin.ignore(); // очищаем буфер
    getline(cin, productName);
    
    cout << "Введите количество единиц: ";
    cin >> quantity;
    cout << "Введите цену за единицу: ";
    cin >> price;

    outputFile << productName << " " << quantity << " " << price << endl;
    outputFile.close();
    
    string successMessage = "Товар успешно добавлен: " + productName + ", количество: " + to_string(quantity) + ", цена: " + to_string(price);
    cout << "Товар успешно добавлен!" << endl;
    writeToOutput(successMessage);
}

//меньше опред значения цены
void uslovie(){
    int usl;
    cout << "Enter the maximum price for the product you want to see: ";
    cin >> usl;
    vector<Product> products = readProductsFromFile();
    bool found = false;
    for (const auto& product : products){
        if (product.price < usl){
            string productInfo = product.name + " " + to_string(product.quantity) + " " + to_string(product.price);
            cout << productInfo << endl;
            writeToOutput("Найден товар: " + productInfo);
            found = true;
        }
    }
    
    if (!found) {
        cout << "Товары с ценой меньше " << usl << " не найдены" << endl;
        writeToOutput("Товары с ценой меньше " + to_string(usl) + " не найдены");
    }
}

int main() {
    int vibor;
    string par;
    // Очищаем файл output.txt при запуске программы
    ofstream clearFile("output.txt");
    clearFile.close();
    do {
        cout << "\n=== Меню ===" << endl;
        cout << "1. Добавить товар" << endl;
        cout << "2. Поиск товара" << endl;
        cout << "3. Сортировка товаров" << endl;
        cout << "4. Вывод данных по запросу пользователя" << endl;
        cout << "0. Завершить программу" << endl;
        cout << "Введите ваш выбор: ";
        cin >> vibor;
        switch (vibor) {
        case 1:
            dobav();
            break;
        case 2:
            cout << "Введите название товара для поиска: ";
            cin.ignore();
            getline(cin, par);
            poisk(par);
            break;
        case 3:
            sortProducts();
            break;
        case 4:
            cin.ignore();
            uslovie();
            break;
        case 0:
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (vibor != 0);
    return 0;
}