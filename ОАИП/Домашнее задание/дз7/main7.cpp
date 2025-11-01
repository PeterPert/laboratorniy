#include <iostream> 
#include <cstring>
using namespace std;

bool isPalindrome(char* str) {  
    char* start = str;           
    char* end = str;             
    while (*end != '\0') {
        end++;
    }
    end--;  // отступаем от нуль-терминатора к последнему символу
    while (start < end) {
        if (*start != *end) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

int main() {
    const int max_s = 1000;
    char str[max_s];
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    bool res = isPalindrome(str);
    if (res) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
}
