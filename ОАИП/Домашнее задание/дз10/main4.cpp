#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    ifstream inFile("source.txt"); 
    if (inFile.fail()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }
    ifstream inputFile("source.txt");
    ofstream outputFile("copy.txt");
    int lineCount = 0;
    string line;
    if (inputFile.is_open() && outputFile.is_open()) {
        while (getline(inputFile, line)) {
            outputFile << line << "\n";
            lineCount++;
        }

        inputFile.close();
        outputFile.close();
        cout << "Количество скопированных строк: " << lineCount << endl;
    } else {
        cout << "Ошибка при открытии файлов для копирования!\n";
        return 1;
    }
}
