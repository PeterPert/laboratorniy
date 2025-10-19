#include <iostream> //Поиск самого длинного слова
#include <cstring>
using namespace std;
int main() {
    const int max_s = 100;
    char str[max_s];
    
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    
    const char delimiters[] = " ";
    char* token = strtok(str, delimiters);
    char cur[max_s] = "";  
    int k = 0;
    
    while (token != nullptr) { 
        int len = strlen(token);
        if (len > k) {
            k = len;  
            strcpy(cur, token);
        }
        token = strtok(nullptr, delimiters);
    }
    cout << "Самое длинное слово: " << cur << endl;
}