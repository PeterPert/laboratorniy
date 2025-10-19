#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <algorithm>
using namespace std; 
int main() {
    string str;
    getline(cin, str);
    istringstream s1(str);
    string word;
    string res = "";
    while (s1 >> word) {
        reverse(word.begin(), word.end());
        res = res + word + " ";
    }
    cout << res << endl;
}
