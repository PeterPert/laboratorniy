#include <iostream>
using namespace std;

int main() {
    int const n = 15;
    double A[n];
    cout << "Введите последовательность из " << n << " чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    double min = A[0];
    double max = A[0];
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
    cout << "kmin" << kmin << endl;
    cout << "kmax" << kmax << endl;
    if (kmax == 0 and kmin == 1) {
        for (int i = 0; i < n; i++) {
            A[i] = A[i] / 2;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
}