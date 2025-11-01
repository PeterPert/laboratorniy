#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;
struct Command {
    string name;  
    int value;    
};

void parseCommand(const char* input, vector<Command>& buffer) {
    const char* p = input;
    while (*p != '\0') {
        string name;
        while (*p != ' ' && *p != '\0') {
            name += *p;
            p++;
        }
        
        while (*p == ' ') {
            p++;
        }
        
        int value = 0;
        if (isdigit(*p) || *p == '-') {
            while (*p != ' ' && *p != '\0') {
                value = value * 10 + (*p - '0');
                p++;
            }
        }
        Command cmd;
        cmd.name = name;
        cmd.value = value;
        buffer.push_back(cmd);

        while (*p == ' ') {
         p++;
        }
    }
}

int main() {
    vector<Command> buffer;
    string str;
    while (str != "0") {
        getline(cin, str);
        if (str == "0") {
            break;
        }
        parseCommand(str.c_str(), buffer);
        }
    for (const auto& cmd : buffer) {
        cout << "Command: " << cmd.name << ", Value: " << cmd.value << endl;
    }
    return 0;
}