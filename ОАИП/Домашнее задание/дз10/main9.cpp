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
    map<string, vector<double>> temp;
    ifstream File ("tempurature_data.txt");
    string line;
    vector<string> name;
    while (getline(File,line)) {
        stringstream ss(line);
        string m;
        double n;
        ss >> m >> n;
        temp[m].push_back(n);
    }
    ofstream outputFile("report.txt" , ios::app);
    int i = 1;
    for (auto &mas:temp){
        auto max_it = max_element(mas.second.begin(), mas.second.end());
        auto min_it = min_element(mas.second.begin(), mas.second.end());
        double sum = accumulate(mas.second.begin(), mas.second.end(), 0.0);
        int n = mas.second.size();
        int u = sum / n; 
        string res = "Sensor" + to_string(i) + "max:" + to_string(*max_it) + "min:" + to_string(*min_it) + "avg:" + to_string(u);
        outputFile << res << endl;
    }
    File.close();
}