#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    ifstream inFile("input.txt"); 
    if (inFile.fail()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }
    string word;
    int wordCount = 0;
    while (inFile >> word) {
        wordCount++;
    }
    cout << "Количество слов в файле: " << wordCount << endl;
    inFile.close();
    return 0;
}