#include <iostream>
using namespace std;

union Variant {
    int intValue;     
    double doubleValue; 
    char charValue;     
};

int main() {
    Variant data;
    char typeChoice;
    do{
        cout << "Выберите тип данных (i - целое число, d - число с плавающей запятой, c - символ): ";
        cin >> typeChoice;
        if (typeChoice == 'i' || typeChoice == 'I') {
            cout << "Введите целое число: ";
            cin >> data.intValue;
            cout << "Вы ввели: " << data.intValue << endl;
        }
        else if (typeChoice == 'd' || typeChoice == 'D') {
            cout << "Введите число с плавающей запятой: ";
            cin >> data.doubleValue;
            cout << "Вы ввели: " << data.doubleValue << endl;
        }
        else if (typeChoice == 'c' || typeChoice == 'C') {
            cout << "Введите символ: ";
            cin >> data.charValue;
            cout << "Вы ввели: " << data.charValue << endl;
        }
        else {
            cout << "Неверный выбор типа данных!" << endl;
            return 1;
        }
    }while(!typeChoice == 'j' );
    return 0;
}