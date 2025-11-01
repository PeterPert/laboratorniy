#include <iostream> 
#include <cstring>
using namespace std;
int main(){
    const int max_s = 1000;
    char str[max_s];
    char ch;
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    cout << "Введите символ: ";
    cin >> ch;
    int k = 0;
    char *ptr = str;
    while (*ptr != '\0') {
        if (*ptr == ch) {
            k++;
        }
        ptr++;
    }
    cout << k << endl;
}
