#include <iostream> 
#include <cstring>
#include<vector>
#include <cmath>
using namespace std;
double computeRMS(const vector<double>& signal) {
    const double* p = signal.data();
    int len = signal.size();
    double sum = 0;
    for (int i = 0; i < len; i++){
        sum += pow(*p, 2);
        p++;
    }
    sum = sum / len;
    return sqrt(sum);
}

int main() {
    vector<double> signal = {2.0, 3.0, 1.0, 4.0, 3.0};
    double res = computeRMS(signal);
    cout << res << endl;
}
