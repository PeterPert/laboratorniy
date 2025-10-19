#include <iostream>
#include <string>
using namespace std;
int main() {
    string str;
    int shift;
    cout << "строка: ";
    getline(cin, str);
    cout << "Сдвиг: ";
    cin >> shift;
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c >= 'A' and c <= 'Z') {
            str[i] = (c - 'A' + shift) % 26 + 'A';
        } 
        else if (c >= 'a' and c <= 'z') {
            str[i] = (c - 'a' + shift) % 26 + 'a';
        }
    }
    cout << str << endl;
}