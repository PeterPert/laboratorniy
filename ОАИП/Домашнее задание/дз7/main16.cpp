#include <iostream>
#include <vector>
using namespace std;

void analyzePressure(const vector<double>& data, double& min, double& max, double& avgVal) {
    const double* p = data.data();
    min = *p;
    max = *p;
    double sum = 0.0;
    
    const double* end = p + data.size(); 
    while (p < end) {
        if (*p < min) {
            min = *p;
        }
        
        if (*p > max) {
            max = *p;
        }
        
        sum += *p;
        p++;
    }
    avgVal = sum / data.size();
}

int main() {
    vector<double> pressure = {101.3, 100.8, 101.9, 100.5, 102.0};
    double minPressure, maxPressure, avgPressure;
    analyzePressure(pressure, minPressure, maxPressure, avgPressure);
    cout << "Min pressure: " << minPressure << endl;
    cout << "Max pressure: " << maxPressure << endl;
    cout << "Average pressure: " << avgPressure << endl;
    return 0;
}