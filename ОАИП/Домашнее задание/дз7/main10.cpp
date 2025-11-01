#include <iostream> 
#include <cstring>
using namespace std;
int myStrCmp(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int main() {
    const int max_s = 1000;
    char str1[max_s];
    cout << "Введите строку: ";
    cin.getline(str1, max_s);
    char str2[max_s];
    cout << "Введите подстроку: ";
    cin.getline(str2, max_s);
    cout << myStrCmp(str1, str2) << endl;
}
