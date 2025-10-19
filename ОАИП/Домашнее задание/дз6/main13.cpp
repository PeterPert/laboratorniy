#include <iostream> //удаление символа
#include <cstring>
using namespace std;
int main() {
    const int max_s = 100;
    char str[max_s];
    char res[max_s] = "";
    
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    char ch;
    cout << "Введите символ для удаления: ";
    cin >> ch;
    
    int len = strlen(str);
    int j = 0;
    
    for (int i = 0; i < len; i++) {
        if (str[i] != ch) {
            res[j] = str[i];
            j++;
        }
    }
    res[j] = '\0';
    cout << res << endl;
    return 0;
}