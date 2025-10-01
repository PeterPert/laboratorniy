#include <iostream>
using namespace std;

int main() {
    int const n = 15;
    double a[n];
    cout << "Введите последовательность из " << n << " чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    double max = a[0];
    int kmax = 0;
    double min = a[0];
    int kmin = 0;
    double temp1;
    double temp2;

    for (int i = 0; i < n; i++) { //поиск макс
        if (a[i] > max) {
            max = a[i];
            kmax = i;
        }
    }
    temp1 = a[n - 1]; // замена мест макс
    a[n - 1] = max;
    a[kmax] = temp1;

    for (int i = 0; i < n; i++) { // посик мин 
        if (a[i] < min) {
            min = a[i];
            kmin = i;
        }
    }
    temp2 = a[0]; // замена мест мин 
    a[0] = min;
    a[kmin] = temp2;

    for (int i = 0; i < n; i++) {
        cout << a[i] <<" ";
    }
}