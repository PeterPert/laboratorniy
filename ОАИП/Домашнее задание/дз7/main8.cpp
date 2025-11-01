#include <iostream> 
#include <cstring>
using namespace std;

const char* findSubstring(const char* text, const char* word) {
    int word_len = strlen(word);
    while (*text != '\0') {
        const char* text_ptr = text;
        const char* word_ptr = word;
        int k = 0;
        while (*word_ptr != '\0' && *text_ptr == *word_ptr) {
            text_ptr++;
            word_ptr++;
            k++;
        }

        if (k == word_len) {
            return text+1;
        }
        
        text++;  
    }
    
    return nullptr;  
}

int main() {
    const int max_s = 1000;
    char str[max_s];
    cout << "Введите строку: ";
    cin.getline(str, max_s);
    char str1[max_s];
    cout << "Введите подстроку: ";
    cin.getline(str1, max_s);
    
    const char* result = findSubstring(str, str1);
    
    if (result != nullptr) {
        cout << "Подстрока найдена по индексу: " << (result - str) << endl;
    } 
    else {
        cout << "Подстрока не найдена" << endl;
    }
}