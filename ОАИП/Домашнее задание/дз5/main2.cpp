#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;
int main() {
    vector<int> numbers;
    for (int i = 1; i <= 10; ++i) {
        numbers.push_back(i);
    }
    for_each(numbers.begin(), numbers.end(), [](int& num) { //Чтобы захватить переменные по ссылке (и изменять их внутри лямбда-функции), используйте &
        num *= 2;  
        });

    cout << "Вектор после умножения на 2: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
}