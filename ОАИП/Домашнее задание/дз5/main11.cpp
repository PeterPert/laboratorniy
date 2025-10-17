#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
using namespace std;
int main() {
    vector<double> vec = {
        3.142, 7.891, 1.234, 9.876, 0.543, 5.678, 2.109, 8.765, 4.321, 6.987,
        0.023, 3.456, 7.890, 1.234, 9.876, 5.432, 8.901, 2.345, 6.789, 0.987,
        4.321, 7.654, 1.098, 3.210, 9.876, 5.432, 8.765, 2.109, 6.543, 0.321,
        4.567, 7.890, 1.234, 9.876, 5.432, 8.901, 2.345, 6.789, 0.123, 4.567,
        7.890, 1.234, 3.456, 9.876, 5.432, 8.765, 2.109, 6.543, 0.987, 4.321
    };
    vec.erase(remove_if(vec.begin(), vec.end(), [](int x){ 
        return x < 0.1;
        }), vec.end());

    double sum = accumulate(vec.begin(), vec.end(), 0);
    double mid = sum/vec.size();
    cout << mid << endl;

    auto it_max = max_element(vec.begin(), vec.end());
    cout << "макс:" <<*it_max << endl;

    bool abb = all_of(vec.begin(), vec.end(), [](double num) {
        return num > 0.5;
    });
    if (abb) {
        cout << "превышают 0.5" << endl;
    }
    else {
        cout << "есть меньше"<< endl; 
    }

    double m[10];
    for (int i = 0; i < 10; i++ ) {
        auto it_max = max_element(vec.begin(), vec.end());
        double vtr = *it_max;
        m[i] = *it_max;
        vec.erase(remove(vec.begin(), vec.end(), vtr), vec.end());
    }
    for (int i = 0; i < 10; i++) {
        cout << m[i] << endl;
    }
}