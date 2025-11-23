#include <iostream>
#include <chrono>
using namespace std;
long long calculateSum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int N = 1000000; 
    auto start = chrono::high_resolution_clock::now();
    long long result = calculateSum(N);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Сумма чисел от 1 до " << N << ": " << result << endl;
    cout << "Время выполнения: " << duration.count() << " миллисекунд" << endl;
    return 0;
}