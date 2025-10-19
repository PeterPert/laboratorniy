#include <iostream>
#include <string>
#include <cctype>
using namespace std; 
int main() {
    string str;
    getline(cin, str);
    char v[] = ".?!";
    str[0] = toupper(str[0]);
    for (int i = 1; i < str.length(); i++) {
        for (int j = 0; j < 3; j++) {
            if (str[i] == v[j]) {
                if (i+1 < str.length() and str[i+1] == ' ') {
                    str[i+2] = toupper(str[i+2]);
                }
                else if( i+1 < str.length() and isalpha(str[i+1])) {
                    str[i+1] = toupper(str[i+1]);
                }
            } 
        } 
    }
    cout << str << endl;
}