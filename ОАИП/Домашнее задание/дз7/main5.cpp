#include <iostream> 
#include <cstring>
using namespace std;
int main(){
    const int max_s = 1000;
    char str[max_s];
    char ch = '_';
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    char *ptr = str;
    while (*ptr != '\0') {
        if (*ptr == ' ') {
            *ptr = ch;
        }
        ptr++;
    }
    cout << str << endl;
}