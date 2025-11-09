#include <iostream>
#include <cstring>
using namespace std;

void sortWords(char **words, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                char *temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

int main() {
    int wordCount;
    cout << "Введите количество слов: ";
    cin >> wordCount;
    cin.ignore();
    char **words = new char*[wordCount+1];
    for (int i = 0; i < wordCount; ++i) {
        char buffer[100];
        cin.getline(buffer, 100);
        words[i] = new char[strlen(buffer) + 1];
        strcpy(words[i], buffer);
    }
    
    // Вывод исходного массива
    cout << "\nИсходный массив слов:" << endl;
    for (int i = 0; i < wordCount; ++i) {
        cout << words[i] << endl;
    }
    
    sortWords(words, wordCount);
    
    // Вывод отсортированного массива
    cout << "\nОтсортированный массив слов:" << endl;
    for (int i = 0; i < wordCount; ++i) {
        cout << words[i] << endl;
    }
    
    // Освобождение памяти
    for (int i = 0; i < wordCount; ++i) {
        delete[] words[i];
    }
    delete[] words;
    return 0;
}