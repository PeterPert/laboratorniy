#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    ifstream inFile("input.txt");
    if (inFile.fail()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close(); 
    return 0;
}