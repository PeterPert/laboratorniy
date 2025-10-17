#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <string>
#include <cctype> // to lower
using namespace std;
int main() {
    string str; 
    cout << "Введите строку: ";
    getline(cin, str);
    string str1;
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i]) == 1) {
            str1 += "";       
        }
        else {
            str1 += str[i];
        }
    }
    cout << str1 << endl;
}