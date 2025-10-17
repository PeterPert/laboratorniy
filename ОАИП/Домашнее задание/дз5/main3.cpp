#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;
int main() {
    vector<int> numbers = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
    auto max = max_element(numbers.begin(), numbers.end(), [](int a, int b) {
        return a < b;  // Лямбда должна возвращать bool
        });
    cout << *max << endl; // max-указатель на элемент, а * выдает уже сам элемент 
}
