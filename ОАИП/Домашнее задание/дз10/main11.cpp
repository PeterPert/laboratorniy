#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <numeric>
using namespace std;
int main() {
    ifstream infile("vibration_log.txt");
    double line;
    vector<double> vib;
    while(infile >> line) {
        vib.push_back(line);
    }
    vib.erase(remove_if(vib.begin(), vib.end(), [](double n) { return n < 0.05; }), vib.end());
    double total = accumulate(vib.begin(), vib.end(), 0.0);
    int kol = vib.size();
    double avg = total / kol;
    auto max_it = max_element(vib.begin(), vib.end());
    auto min_it = min_element(vib.begin(), vib.end());
    string resvib;
    for (auto elem: vib ) {
        resvib += to_string(elem) + "  ";
    }
    string res = "количество измерений:" + to_string(kol) + "\n" + 
    "Фильтрованные значения (>0.05):" + resvib + "\n" + 
    "Среднее значение:" + to_string(avg) + "\n" +
    "Минимум:" + to_string(*min_it) + "\n" + 
    "Максимум:" + to_string(*max_it);
    ofstream outfile("vibration_report.txt"); 
    outfile << res << endl;
    cout << "Анализ вибрационных данных завершён. Отчёт сохранён в vibration_report.txt" << endl;
    outfile.close();
}