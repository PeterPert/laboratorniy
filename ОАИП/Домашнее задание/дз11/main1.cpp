#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream inputFile("book.txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл book.txt" << endl;
        return 1;
    }
    ofstream outputFile("results.txt");
    string searchWord = "Герой";
    string line;
    int lineNumber = 0;
    int totalCount = 0;
    outputFile << "Поиск слова: '" << searchWord << "'\n";
    outputFile << "Строка\tПозиция\tСлово\n";
    while (getline(inputFile, line)) {
        lineNumber++;
        size_t pos = 0;
        while ((pos = line.find(searchWord, pos)) != string::npos) {
            outputFile << lineNumber << "\t" << pos << "\t" << searchWord << endl;
            pos += searchWord.length();
            totalCount++;
        }
    }
    outputFile << "\nВсего найдено: " << totalCount << endl;
    inputFile.close();
    outputFile.close();
    return 0;
}