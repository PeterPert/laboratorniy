#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
using namespace std;
int main() {
    std::vector<int> vec ={247, 132, -15, 89, 276, 42, 195, -23, 163, 291, 77, 218, -38, 155, 104, 265, 13, 188, 7, 299};
    vec.erase(remove_if(vec.begin(), vec.end(), [](int x){ 
        return x < 0;
        }), vec.end());
    
    auto it_max = max_element(vec.begin(), vec.end());
    cout << *it_max << endl;
    auto it_min = min_element(vec.begin(), vec.end());
    cout << *it_min <<endl;
    int sum = accumulate(vec.begin(), vec.end(), 0);
    double mid = sum/vec.size();
    cout << mid << endl;

    bool abb = all_of(vec.begin(), vec.end(), [](double num) {
        return num >= 10 || num <= 90;
    });
    if (abb) {
        cout << "работал все время yes" << endl;
    }
    else {
        cout << " не всё время no"<< endl; 
    }

    sort(vec.begin(), vec.end(), [](int a, int b) { return a < b; });
    cout << vec[vec.size()/2] << endl;
}