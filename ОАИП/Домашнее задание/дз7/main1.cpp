#include <iostream> 
#include <cstring>
using namespace std;
int myStrLen(const char* str) {
    const char* ptr = str;
    int len = 0; 
    while (*ptr != '\0') {
        ptr++;
        len++;
    }
    return len;
}

int main() {
    const int max_s = 1000;
    char str[max_s];
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    
    int length = myStrLen(str);
    cout << "Длина строки: " << length << endl;
}