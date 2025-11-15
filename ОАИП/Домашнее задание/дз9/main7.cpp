#include <iostream>
#include <memory>
#include <cstring>
#include <cctype>

using namespace std;

bool isVowel(char c) {
    c = tolower(c);
    char buffer[] = "aeiouy";
    for (int i = 0; i < strlen(buffer); i++){
        if (buffer[i] == c){
            return true;
        }
    }
    return false; 
}

bool isConsonant(char c) {
    c = tolower(c);
    return isalpha(c) && !isVowel(c);
}

int main() {
    const int MAX_LENGTH = 100;
    char inputBuffer[MAX_LENGTH];
    cout << "Введите строку: ";
    cin.getline(inputBuffer, MAX_LENGTH);
    int length = strlen(inputBuffer);
    unique_ptr<char[]> charArray = make_unique<char[]>(length + 1);
    strcpy(charArray.get(), inputBuffer);
    // Подсчет гласных и согласных
    int vowels = 0, consonants = 0;
    for (int i = 0; i < length; i++) {
        if (isVowel(charArray[i])) {
            vowels++;
        }
        else if (isConsonant(charArray[i])) {
            consonants++;
        }
    }
    cout << "Гласные: " << vowels << ", Согласные: " << consonants << endl;
    //толкьо гласные
    unique_ptr<char[]> arr = make_unique<char[]>(vowels + 1);
    int p = 0;
    for (int i = 0; i < length; i++) {
        if (isVowel(charArray[i])) {
            arr[p] = charArray[i];
            p++;
        }
    }
    cout << "Только гласные: ";
    for (int i = 0; i < vowels; i++) {
        cout << arr[i];
    }
    cout << endl;
    cout << endl;
    cout << "Память автоматически освободится при выходе из области видимости." << endl;
}