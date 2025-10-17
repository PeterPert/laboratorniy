#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
using namespace std;
int main() {
    vector<int> vec ={356, 287, 312, 245, 398, 223, 331, 269, 385, 207, 
        294, 367, 258, 341, 216, 379, 278, 325, 234, 391, 
        301, 349, 241, 363, 211, 318, 252, 372, 228, 404};
    
    int sum = accumulate(vec.begin(), vec.end(), 0);
    cout << "сумма:" << sum << endl;

    double mid = sum/vec.size();
    cout << mid << endl;

    auto it_max = max_element(vec.begin(), vec.end());
    cout << "макс:" <<*it_max << endl;
    auto it_min = min_element(vec.begin(), vec.end());
    cout << "мин:" <<  *it_min <<endl;

    vec.erase(remove_if(vec.begin(), vec.end(), [mid](int x){ 
        return x*0.8 > mid;
        }), vec.end());
    for (int num : vec) {
        cout << num << " ";
    }
}
