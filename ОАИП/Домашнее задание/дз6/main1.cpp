#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype> // to lower
using namespace std;
int main() {
    string mystr; 
    cout << "Введите строку: ";
    getline(cin, mystr); 
    
    string str1;
    str1 = mystr;
    reverse(str1.begin(), str1.end());
    bool tr = true;
    
    mystr.erase(remove(mystr.begin(), mystr.end(), ' '), mystr.end());
    str1.erase(remove(str1.begin(), str1.end(), ' '), str1.end());
    transform(mystr.begin(), mystr.end(), mystr.begin(), ::tolower);
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    
    cout << "Оригинал без пробелов: " << mystr << endl;
    cout << "Развернутая без пробелов: " << str1 << endl;
    
    for (int i = 0; i < mystr.length()/2; i++) {
        if (mystr[i] != str1[i]) {
            tr = false;
            break;
        }
    }
    
    if (tr) {
        cout << "полиндром yes" << endl;
    }
    else {
        cout << "нет no" << endl;
    }
    return 0;
}
