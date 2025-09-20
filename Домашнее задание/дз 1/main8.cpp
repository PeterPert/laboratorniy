#include <iostream>
#include <string>

using namespace std;

int main() {
    int a = 0;//количество гласных
    string v = "aeiouAEIOUаеёиоуыэюяАЕЁИОУЫЭЮЯ";
    char c;

    setlocale(LC_ALL, "");
    wcout << L"Введите строку: ";
    while (cin.get(c) and c != '\n') {
        if (v.find(c) != string::npos) {
            a++;
        }
    }
    setlocale(LC_ALL, "");
    wcout << L"Количество гласных: " << a << endl;
    return 0;
}