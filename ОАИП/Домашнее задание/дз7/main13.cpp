#include <iostream> 
#include <cstring>
using namespace std;
void parseTelemetry(const char* data) {
    const char* current = data;
    while (*current != '\0') {
        while (*current == ' ' || *current == ';') {
            current++;
        }
    
        const char* name_start = current;
        while (*current != ':' && *current != '\0') {
            current++;
        }
        cout.write(name_start, current - name_start);
        cout << ": ";

        current++;

        const char* value_start = current;
        while (*current != ';' && *current != '\0') {
            current++;
        }
        cout.write(value_start, current - value_start);
        cout << endl;
    }  
}

int main() {
    const int max_s = 1000;
    char str1[max_s];
    cout << "Введите строку: ";
    cin.getline(str1, max_s);
    parseTelemetry(str1);
    return 0;
}

