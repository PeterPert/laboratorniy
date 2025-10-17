#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
using namespace std;
int main() {
    vector<double> temp = {15, 8, 23, 4, 56, 19, 7, 31, 14, 28,
                                -3, 37, 14, 25, 9, 33, -56, -21, 17, 12}; 
    temp.erase(remove_if(temp.begin(), temp.end(), [](int x){ 
        return x<-50.0 || x>50.0;
        }), temp.end());
    auto it_max = max_element(temp.begin(), temp.end());
    cout << *it_max << endl;
    auto it_min = min_element(temp.begin(), temp.end());
    cout << *it_min <<endl;
    int sum = accumulate(temp.begin(), temp.end(), 0);
    double mid = sum/20;
    cout << mid << endl;
    bool abb = all_of(temp.begin(), temp.end(), [](double num) {
        return num > -10;
    });
    if (abb) {
        cout << "все больше -10 ";
    }
    else {
        cout << " есть меньше -10" << endl; 
    }
}
    