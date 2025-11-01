#include <iostream> 
#include <cstring>
using namespace std;

void reverse(char* str) {
    if (str == nullptr) return;  
    char* start = str;           
    char* end = str;             
    while (*end != '\0') {
        end++;
    }
    end--;  // отступаем от нуль-терминатора к последнему символу
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main() {
    const int max_s = 1000;
    char str[max_s];
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    reverse(str);
    cout << str << endl;
}
