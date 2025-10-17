#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
#include <random>
using namespace std;
int main() {
    vector<int> vec(50);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 180);
    for (auto& element : vec) {
        element = dis(gen);
    }
    for (const auto& element : vec) {
        cout << element << " ";
    }
    cout << endl;
    // удаляет больше 120
    vec.erase(remove_if(vec.begin(), vec.end(), [](int x){ 
        return x > 120;
        }), vec.end());
    // средняя скорость 
    int sum = accumulate(vec.begin(), vec.end(), 0);
    double mid = sum/vec.size();
    cout << mid << endl;
    // двигался ли постоянно 
    bool abb = all_of(vec.begin(), vec.end(), [](double num) {
        return num > 0;
    });
    if (abb) {
        cout << "двигался постоянно" << endl;
    }
    else {
        cout << " скорость была < 0"<< endl; 
    }
    //10 макс скоростей
    int m[10];
    for (int i = 0; i < 10; i++ ) {
        auto it_max = max_element(vec.begin(), vec.end());
        int vtr = *it_max;
        m[i] = *it_max;
        vec.erase(std::remove(vec.begin(), vec.end(), vtr), vec.end());
    }
    for (int i = 0; i < 10; i++) {
        cout << m[i] << endl;
    }
}