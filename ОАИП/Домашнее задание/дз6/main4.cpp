#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int main() {
    string a;
    string b; 
    cout << "Введите строку 1 : ";
    getline(cin, a);
    cout << "Введите строку 2 : ";
    getline(cin, b);
    bool rt = true;
    int h = 0;
    for (int i = 0; i < b.length();i++) {
        for (int j = 0; j <a.length();j++) {
            if (b[i] == a[j]) {
                h++;
                break;
            }
        }
    }
    if (h == b.length()) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }

}
