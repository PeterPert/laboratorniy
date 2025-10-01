#include <iostream>
using namespace std;

int main() {
    int const n = 10;
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
    
    if (kmax == 1 and kmin == 4) {
        for (int i = kmin+1; i < n; i++) {
            A[i] = max;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
}