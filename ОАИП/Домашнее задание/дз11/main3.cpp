#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream in("application.log", ios::binary);
    ofstream index("index.txt");
    
    const int MAX_SIZE = 1000000; // 1 МБ
    int partNum = 1;
    int currentSize = 0;
    string line;
    
    // Определяем размер файла
    in.seekg(0, ios::end);
    int fileSize = in.tellg();
    in.seekg(0, ios::beg);
    index << "Части лог-файла:\n";
    index << "Общий размер: " << fileSize << " байт\n\n";
    while (in.tellg() < fileSize) {
        if (currentSize == 0) {
            string name = "part" + to_string(partNum) + ".txt";
            index << name << endl;
        }
        streampos lineStart = in.tellg();
        if (!getline(in, line)) break;
        
        // Вычисляем реальный размер строки с учетом \n
        streampos lineEnd = in.tellg();
        int lineSize;
        
        if (in.eof()) {
            lineSize = line.length();
        } else {
            lineSize = lineEnd - lineStart;
        }
        
        // Проверяем, не превысит ли строка лимит
        if (currentSize + lineSize > MAX_SIZE && currentSize > 0) {
            in.seekg(lineStart);
            currentSize = 0;
            partNum++;
            continue;
        }
        
        ofstream out("part" + to_string(partNum) + ".txt", ios::app);
        out << line << endl;
        out.close();
        currentSize += lineSize;
    }
    in.close();
    index << "\nВсего частей: " << partNum << endl;
    index.close();
    return 0;
}