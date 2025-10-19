#include <iostream>
#include <string>
using namespace std;

int main() {
    string input;
    cout << "Введите строку для сжатия: ";
    cin >> input;
    string result = "";
    int count = 1;
    char current = input[0];
    
    for (int i = 1; i < input.length(); i++) {
        if (input[i] == current) {
            count++;
        } else {
            result += current + to_string(count);
            current = input[i];
            count = 1;
        }
    }
    // Добавляем последнюю последовательность
    result += current + to_string(count);
    cout << "Сжатая строка: " << result << endl;
}