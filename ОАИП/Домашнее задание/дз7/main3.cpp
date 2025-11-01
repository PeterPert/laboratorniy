#include <iostream> 
#include <cstring>
using namespace std;
void myStrCat(char* dest, const char* src) {
    int len1 = strlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[len1 + i] = src[i];
        i++;
    }
    dest[len1 + i] = '\0';
}

int main() {
    const int max_s = 1000;
    char str[max_s];
    char etc[max_s];
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    cout << "Введите строку: ";
    cin.getline(etc, max_s);
    myStrCat(etc, str);
    cout << etc << endl;
}