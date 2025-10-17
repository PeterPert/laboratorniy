#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
using namespace std;
int main() {
    vector<int> vec = {
        45, 12, 78, 23, 67, 34, 89, 56, 21, 9,
        73, 38, 15, 62, 29, 80, 47, 18, 65, 32,
        7, 54, 26, 71, 39, 14, 58, 33, 76, 41,
        19, 63, 28, 75, 42, 17, 69, 35, 82, 48,
        3, 51, 24, 68, 37, 11, 59, 30, 77, 44
    };
    auto it_min = min_element(vec.begin(), vec.end());
    cout << "мин:" <<  *it_min <<endl;

    auto it_max = max_element(vec.begin(), vec.end());
    int max = *it_max;
    bool abb = all_of(vec.begin(), vec.end(), [max](double num) {
        return num > 0.95*max;
    });
    if (abb) {
        cout << "только выше" << endl;
    }
    else {
        cout << "есть ниже 95%"<< endl; 
    }

    int crd = vec.end()-vec.begin();
    cout << crd << endl;

    sort(vec.begin(), vec.end(), [](int a, int b) { return a < b; });
    cout << vec[vec.size()/2] << endl;
}

    
