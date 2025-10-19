#include <iostream>
#include <cstring>
using namespace std;
int main() {
    const int max_sz = 100;
    char str1[max_sz];
    char str2[max_sz];
    cout << "Введите строку A: ";
    cin.getline(str1, max_sz);
    cout << "Введите строку B: ";
    cin.getline(str2, max_sz);
    
    int max_len = 0;
    char longest_common[max_sz] = "";
    for (int i = 0; i < strlen(str1); i++) {
        for (int j = 0; j < strlen(str2); j++) {
            if (str1[i] == str2[j]) {
                int len = 0;
                while (str1[i + len] == str2[j + len] and str1[i + len] != '\0' and str2[j + len] != '\0') {
                    len++;
                }
                if (len > max_len) {
                    max_len = len;
                    strncpy(longest_common, &str1[i], len); //longest_common - целевой массив, куда копируем &str[i] - указатель на i-й символ в исходной строке str len - колво символов для копирования
                    longest_common[len] = '\0';
                }
            }
        }
    }
    if (max_len > 0) {
        cout << longest_common << endl;
    }
}