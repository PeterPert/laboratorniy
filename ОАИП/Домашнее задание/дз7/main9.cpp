#include <iostream> 
#include <cstring>
using namespace std;
const char* del(const char* text) {
    const int max_s = 1000;
    static char text1[max_s]; // Добавляем static для сохранения данных после выхода из функции
    char* text_ptr = text1; 
    while (*text != '\0') {
        if (*text != ' ') {
            *text_ptr = *text;
            text_ptr++;
        }
        text++; 
    }
    *text_ptr = '\0';
    return text1;
}

int main() {
    const int max_s = 1000;
    char str[max_s];
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    const char *res = del(str);
    cout << res << endl;
    return 0;
}