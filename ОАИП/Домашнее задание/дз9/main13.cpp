#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <numeric>
using namespace std;
int main(){
    unique_ptr<string> part1 = make_unique<string>("Sensor data:");
    unique_ptr<string> part2 = make_unique<string>("Voltage stable.");
    unique_ptr<string> part3 = make_unique<string>("System nominal.");
    vector<unique_ptr<string>> reportParts;
    reportParts.push_back(move(part1));
    reportParts.push_back(move(part2));
    reportParts.push_back(move(part3));
    
    auto concatParts = [&](){string result; for (const auto& part : reportParts) {
            result += *part + "\n";
        }
        return result;
    };
    
    auto countWord = [](const string& text, const string& word){
        int count = 0;
        int pos = 0;
        while ((pos = text.find(word, pos)) != string::npos) {  //text.find выдает указатель на начало data в text и присваивает его pos, когда будет конец text, pos ничего содержать не будет и программа закроется
            count++;
            pos += word.length();
        }
        return count;
    };
    
    string reportText = concatParts();
    int dataCount = countWord(reportText, "data");
    
    cout << "Отчёт:\n" << reportText;
    cout << "Слово \"data\" встречается " << dataCount << " раз" << endl;
    return 0;
}
