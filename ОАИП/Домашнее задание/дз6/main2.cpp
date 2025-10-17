#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype> // to lower
using namespace std;
int main() {
    string str; 
    cout << "Введите строку: ";
    getline(cin, str);
    vector<char>res;
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    for (int i = 0; i < str.length(); i++) {
        bool found = find(res.begin(), res.end(), str[i]) != res.end(); //(начало_источника, конец_источника, куда запишем результат преобразования, функция)
        if (found) {
            continue;
        }
        else {
            res.push_back(str[i]);
        }
    }
    for (auto elem:res) {
        cout << elem << " ";
    }
}