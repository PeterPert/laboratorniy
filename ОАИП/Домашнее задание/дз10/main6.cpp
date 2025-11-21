#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла input.txt!" << endl;
        return 1;
    }
    ofstream output("output.txt");
    string line;
    getline(cin, line);
    output << line <<endl;
    while (!line.empty()){
        getline(cin, line);
        output << line <<endl;
    }
    output.close();
}