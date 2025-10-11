#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Введите количество чисел n: ";
    cin >> n;
    int* A = new int[n];
    int max = A[0];
    int k = 0;
    cout << "Введите последовательность из " << n << " чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        if (A[i]%2 != 0) {
            if (A[i] > max) {
                max = A[i];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (A[i] % 2 == 0) {
            k++;
        }
    }
    cout << "наиб из нечет" << max << endl;
    cout << "кол во четных" << k << endl;
}