#include <iostream> 
#include <cstring>
using namespace std;
void myStrCopy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {  
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  
}

int main() {
    const int max_s = 1000;
    char str[max_s];
    char res[max_s] = "";
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    myStrCopy(res, str);
    cout << res << endl;
}
    
