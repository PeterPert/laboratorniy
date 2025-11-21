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
    map<string, vector<double>> power;
    ifstream infile("power_log.txt");
    string line;
    while(getline(infile, line)) {
        stringstream ss(line);
        string first_word;
        string m;
        double n; 
        ss >> first_word >> m >> n;
        power[m].push_back(n);
    }
    ofstream outfile("energy_report.txt");
    for (auto &mas:power){
        int kol = mas.second.size();
        double total = accumulate(mas.second.begin(), mas.second.end(), 0.0);
        double average = total/kol;
        string res = mas.first + ":" + "measurements =" + to_string(kol) + "total =" + to_string(total) + "avg =" + to_string(average);
        outfile << res << endl;
    }
    outfile.close();
}