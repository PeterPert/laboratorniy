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
    int k = 0;
    string line;
    while (getline(inFile, line)) {
        k++;
    }
    inFile.close(); 
    cout << k <<endl;
    return 0;
}