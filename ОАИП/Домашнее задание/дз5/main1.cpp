#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;
int main() {
    vector<int> numbers;
    for (int i = 1; i <= 10; ++i) {
        numbers.push_back(i);
    }

    // Вывод вектора с помощью for_each и лямбда-функции
    cout << "Элементы вектора: ";
    for_each(numbers.begin(), numbers.end(), [](int num) {
        cout << num << " ";
        });
    cout << endl;
    return 0;
}