#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
using namespace std;
int main() {
    vector<int> vec = {
        356, 287, 412, 145, 498, 223,
        331, 269, 385, 407, 294, 367,
        258, 441, 216, 379, 278, 425,
        234, 491, 301, 349, 341, 404
    };
    double sum = accumulate(vec.begin(), vec.end(), 0);
    double mid = sum/vec.size();
    cout << mid << endl;

    auto it_max = max_element(vec.begin(), vec.end());
    cout << "макс:" <<*it_max << endl;
    //отклонения
    vector<int> squares(vec.size());
    transform(vec.begin(), vec.end(), squares.begin(), [mid](int x){ return abs(x-mid); });
    cout << "отклонения: ";
    for (int x : squares) std::cout << x << " ";
    cout << endl;
    
    sort(vec.begin(), vec.end(), [](int a, int b) { return a < b; });
    int m[5];
    for (int i = 0; i<5; i++) {
        m[i] = vec[i];
    }
    for (int i = 0; i<5; i++) {
        cout << m[i] << endl;
    }
}