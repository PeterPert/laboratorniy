#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int main() {
    string str;
    cout << "Введите строку: ";
    getline(cin, str);
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    string b = "aeiouy";
    string c = "bcdfghjklmnpqrstvwxz";
    int g = 0;
    int s = 0;
    for (int i = 0; i < str.length(); i++) {
        if (b.find(str[i]) != string::npos) {
            g++;
        }
        else if (c.find(str[i]) != string::npos) {
            s++;
        }
    }
    cout << g << endl;
    cout << s << endl;
}