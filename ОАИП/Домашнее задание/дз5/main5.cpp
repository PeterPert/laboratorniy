#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
using namespace std;

int main() {
    int n = 20;
    std::vector<int> numb = { 15, 8, 23, 4, 42, 19, 7, 31, 11, 28,
                                3, 37, 14, 25, 9, 33, 6, 21, 17, 12 };

    // Выводим исходный вектор
    std::cout << "Исходный вектор: ";
    for (int num : numb) {
        std::cout << num << " ";
    }

    std::cout << std::endl << std::endl;
    auto max_it = max_element(numb.begin(), numb.end());
    cout << *max_it << endl;

    auto min_it = min_element(numb.begin(), numb.end());
    cout << *min_it << endl;

    int sum = accumulate(numb.begin(), numb.end(), 0);
    int u = sum / n; // сред значение 
    cout << u << endl;

    sort(numb.begin(), numb.end());

    double median;
    if (n % 2 == 0) {
        // Четное количество элементов - медиана это среднее двух центральных
        median = (numb[n / 2 - 1] + numb[n / 2]) / 2.0;
    }
    else {
        // Нечетное количество элементов - медиана это центральный элемент
        median = numb[n / 2];
    }
    cout << median << std::endl;
}