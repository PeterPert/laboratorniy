#include <iostream>
using namespace std;

int main() {
    cout << "Решение системы уравнений:" << endl;
    cout << "2x + 3y = 13" << endl;
    cout << "5x - y = 9" << endl;

    int a1 = 2, b1 = 3, c1 = 13;  // первое уравнение
    int a2 = 5, b2 = -1, c2 = 9;  // второе уравнение
    int a2_new = a2 * 3;
    int b2_new = b2 * 3;
    int c2_new = c2 * 3;

    // Складываем уравнения
    int sum_a = a1 + a2_new;
    int sum_b = b1 + b2_new;
    int sum_c = c1 + c2_new;

    int x_ch = sum_c;
    int x_zn = sum_a;
    double x = (double)x_ch / x_zn;
    double y = 5 * x - 9;

    cout << "Решение:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << endl;
}