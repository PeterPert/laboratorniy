#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла input.txt!" << endl;
        return 1;
    }
    char ch;
    int charCount = 0;
    while (inputFile.get(ch)) {
        charCount++;
    }
    inputFile.close();
    cout << charCount << endl;
    return 0;
}
