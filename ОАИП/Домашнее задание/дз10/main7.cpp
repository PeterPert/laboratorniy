#include <iostream>
#include <fstream>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    ifstream inputFile("numbers.txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла numbers.txt!" << endl;
        return 1;
    }
    int number;
    int count = 0;
    double sum = 0;
    while (inputFile >> number) {
        sum += number;
        count++;
    }
    inputFile.close();
    cout << "Количество чисел: " << count << endl;
    cout << "Сумма: " << sum << endl;
    
    if (count > 0) {
        double average = double((sum) / count);
        cout << "Среднее: " << average << endl;
    } else {
        cout << "Среднее: 0 (файл пустой)" << endl;
    }
    return 0;
}