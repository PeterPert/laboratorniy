#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
using namespace std;
int main() {
    vector<double> vec = {
        3.142, 7.891, 1.234, 9.876, 0.543, 5.678, 2.109, 8.765, 4.321, 6.987,
        0.123, 3.456, 7.890, 1.234, 9.876, 5.432, 8.901, 2.345, 6.789, 0.987,
        4.321, 7.654, 1.098, 3.210, 9.876, 5.432, 8.765, 2.109, 6.543, 0.321,
        4.567, 7.890, 1.234, 9.876, 5.432, 8.901, 2.345, 6.789, 0.123, 4.567,
        7.890, 1.234, 3.456, 9.876, 5.432, 8.765, 2.109, 6.543, 0.987, 4.321
    };

    vec.erase(remove_if(vec.begin(), vec.end(), [](int x){ 
        return x < 0 || x > 12;
        }), vec.end());
    
    double sum = accumulate(vec.begin(), vec.end(), 0);
    double mid = sum/vec.size();
    cout << mid << endl;

    auto it_max = max_element(vec.begin(), vec.end());
    cout << "макс:" <<*it_max << endl;

    auto it_min = min_element(vec.begin(), vec.end());
    cout << "мин:" <<  *it_min <<endl;

    for_each(vec.begin(), vec.end(), [](double num) {
        if (num > 8){
            cout << num << " ";   
        }
    });
    cout << endl;
}