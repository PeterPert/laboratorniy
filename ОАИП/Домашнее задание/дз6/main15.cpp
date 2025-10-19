#include <iostream>
#include <cstring>
using namespace std;

int main() {
    const int max_s = 1000;
    char str1[max_s];
    char str2[max_s];
    char sorted1[max_s];
    char sorted2[max_s];
    
    cout << "Введите первую строку: ";
    cin.getline(str1, max_s);
    cout << "Введите вторую строку: ";
    cin.getline(str2, max_s);
    
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    strcpy(sorted1, str1);
    strcpy(sorted2, str2);
    for(int i = 0; i < len1 - 1; i++) { // Сортируем первую строку (пузырьковая сортировка)
        for(int j = 0; j < len1 - i - 1; j++) {
            if(sorted1[j] > sorted1[j + 1]) {
                char temp = sorted1[j];
                sorted1[j] = sorted1[j + 1];
                sorted1[j + 1] = temp;
            }
        }
    }
    for(int i = 0; i < len2 - 1; i++) {
        for(int j = 0; j < len2 - i - 1; j++) {
            if(sorted2[j] > sorted2[j + 1]) {
                char temp = sorted2[j];
                sorted2[j] = sorted2[j + 1];
                sorted2[j + 1] = temp;
            }
        }
    }
    bool is_anagram = true;
    for(int i = 0; i < len1; i++) {
        if(sorted1[i] != sorted2[i]) {
            is_anagram = false;
            break;
        }
    }
    if(is_anagram) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}