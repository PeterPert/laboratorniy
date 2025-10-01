#include <iostream>
using namespace std;

int main() {
    int const n = 15;
    int A[n];
    cout << "Введите последовательность из " << n << " чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int min = A[1];
    int max = A[0];
    int kmax = 0;
    int kmin = 0;
    for (int i = 0; i < n; i++) { // поиск мин 
        if (A[i] < min) {
            min = A[i];
            kmin = i;
        }
    }

    for (int i = 0; i < n; i++) { //поиск макс
        if (A[i] > max) {
            max = A[i];
            kmax = i;
        }
    }
    if (min == 0 or max == 0) {
        for (int i = 0; i < kmin; i++) {
            A[i] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
}