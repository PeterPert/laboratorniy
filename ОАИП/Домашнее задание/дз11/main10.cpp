#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void createConfig() {
    ofstream file("config.json");
    file << "{\n";
    file << "  \"app_name\": \"My Application\",\n";
    file << "  \"version\": \"1.0.0\",\n";
    file << "  \"settings\": {\n";
    file << "    \"max_connections\": 100,\n";
    file << "    \"timeout\": 30,\n";
    file << "    \"debug_mode\": true\n";
    file << "  },\n";
    file << "  \"database\": {\n";
    file << "    \"host\": \"localhost\",\n";
    file << "    \"port\": 5432,\n";
    file << "    \"username\": \"admin\"\n";
    file << "  }\n";
    file << "}";
    file.close();
    cout << "Конфигурационный файл создан\n";
}

void updateTimeout(int newTimeout) {
    ifstream inFile("config.json");
    vector<string> lines;
    string line;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();
    
    for (string& currentLine : lines) {
        size_t timeoutPos = currentLine.find("\"timeout\"");
        if (timeoutPos != string::npos) {
            size_t colonPos = currentLine.find(":", timeoutPos);
            size_t valueStart = currentLine.find_first_of("1234567890", colonPos); // найди место первого из этих чисел начиная с двоеточия
            size_t valueEnd = currentLine.find_first_not_of("1234567890", valueStart); // найди место первого не из этих чисел начиная с valuestart - это ,
            
            if (valueStart != string::npos && valueEnd != string::npos) {
                currentLine.replace(valueStart, valueEnd - valueStart, to_string(newTimeout));
            }
            break;
        }
    }
    
    ofstream outFile("config.json");
    for (const string& currentLine : lines) {
        outFile << currentLine << endl;
    }
    outFile.close();
}

int main() {
    // Создаем файл если не существует
    ifstream test("config.json");
    if (!test.is_open()) {
        createConfig();
    }
    test.close();
    string line;
    int newTimeout;
    cout << "\nВведите новое значение timeout: ";
    cin >> newTimeout;
    
    updateTimeout(newTimeout);
    cout << "\nОбновленный config.json:\n";
    ifstream updatedFile("config.json");
    while (getline(updatedFile, line)) {
        cout << line << endl;
    }
    updatedFile.close();
    return 0;
}