#include <iostream>
using namespace std;

int main() {
    int const n = 15;
    double A[n];
    cout << "Введите последовательность из " << n << " чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    
    double min = A[1];
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
    if (kmax < kmin) {
        cout << max * min << endl;
    }
}