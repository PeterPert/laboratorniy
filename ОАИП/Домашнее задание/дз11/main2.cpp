#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string filename = "config.txt";
    string searchKey = "timeout=";
    string newValue = "60";
    fstream file(filename, ios::in | ios::out);
    
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return 1;
    }

    vector<string> buffer;
    string line;
    while (getline(file,line)) {
        buffer.push_back(line);
    }

    string content(buffer.begin(), buffer.end());
    size_t keyPos = content.find(searchKey);
    if (keyPos != string::npos) {
        cout << "Найдено в позиции: " << keyPos << endl;
        size_t lineEnd = content.find('\n', keyPos);
        if (lineEnd == string::npos) {
            lineEnd = content.length();
        }
        string originalLine = content.substr(keyPos, lineEnd - keyPos);
        size_t valueStart = keyPos + searchKey.length();
        size_t valueEnd = lineEnd;
        string newLine = searchKey + newValue;
        
        content.replace(keyPos, lineEnd - keyPos, newLine);
        
        file.seekp(0, ios::beg);
        streampos writePos = file.tellp();
        
        file.write(content.c_str(), content.length());
        file.seekp(content.length());
        file.close();
        
        cout << "Изменения успешно сохранены!" << endl;
    } else {
        cout << "Параметр '" << searchKey << "' не найден в файле" << endl;
        file.close();
    }
    
    return 0;
}