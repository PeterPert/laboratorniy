#include <iostream>
#include <string>

using namespace std;
union Variant {
    int intValue;      
    double doubleValue; 
    char charValue;     
};

int main() {
    Variant var;        
    char choice;        
    cout << "Выберите тип данных (i - целое число, d - число с плавающей запятой, c - символ): ";
    cin >> choice;
    switch (choice) {
        case 'i': 
            cout << "Введите целое число: ";
            cin >> var.intValue;
            cout << "Вы ввели: " << var.intValue << endl;
            break;
            
        case 'd': 
            cout << "Введите число с плавающей запятой: ";
            cin >> var.doubleValue;
            cout << "Вы ввели: " << var.doubleValue << endl;
            break;
            
        case 'c': 
            cout << "Введите символ: ";
            cin >> var.charValue;
            cout << "Вы ввели: " << var.charValue << endl;
            break;
            
        default:
            cout << "Ошибка: неверный выбор типа данных!" << endl;
            break;
    }
    return 0;
}