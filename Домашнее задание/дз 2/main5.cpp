#include <iostream>
using namespace std;
int main() {
    int const n = 10;
    int a[n];
    cout << "Введите последовательность из " << n << " чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int min = a[1];
    int max = a[0];
    int kmax = 0;
    int kmin = 0;
    double m;
    for (int i = 0; i < n; i++) { // поиск мин 
        if (a[i] < min) {
            min = a[i];
            kmin = i;
        }
    }
    for (int i = 0; i < n; i++) { //поиск макс
        if (a[i] > max) {
            max = a[i];
            kmax = i;
        }
    }
    if (kmax == 9 and kmin == 4) {
        m = ((double)max + min) / 2; 
        cout << m << endl;
    }
}