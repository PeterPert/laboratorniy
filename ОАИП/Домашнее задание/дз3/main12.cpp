#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
    int a[4][3];
    for (int i = 0; i < 4; i++) {
        cout << "Введите координаты" << i + 1 << "точки" << endl;
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }
    double A[4][5];
    for (int i = 0; i < 4; i++) {
        int h = 0;
        for (int j = 0; j < 5; j++) {
            if (h == 3) {
                A[i][j] = 1;
            }
            else if (h == 4) {
                A[i][j] = -pow(a[i][j - 4], 2) - pow(a[i][j - 3], 2) - pow(a[i][j - 2], 2);
            }
            else {
                A[i][j] = a[i][j];
            }
            h += 1;
        }
    }
    int const n = 4;
    // Прямой ход метода Гаусса
    for (int k = 0; k < n; k++) {
        // Поиск главного элемента в столбце
        int max_row = k;
        for (int i = k + 1; i < n; i++) {
            if (abs(A[i][k]) > abs(A[max_row][k])) {
                max_row = i;
            }
        }
        
        // Перестановка строк
        if (max_row != k) {
            for (int j = 0; j <= n; j++) {
                double temp = A[k][j];
                A[k][j] = A[max_row][j];
                A[max_row][j] = temp;
            }
        }
        
        // Нормализация текущей строки
        double pivot = A[k][k];
        for (int j = k; j <= n; j++) {
            A[k][j] /= pivot;
        }
        
        // Исключение переменной из остальных строк
        for (int i = 0; i < n; i++) {
            if (i != k) {
                double factor = A[i][k];
                for (int j = k; j <= n; j++) {
                    A[i][j] -= factor * A[k][j];
                }
            }
        }
    }
    
    // Решение (последний столбец содержит корни)
    double x[n];
    for (int i = 0; i < n; i++) {
        x[i] = A[i][n];
    }
    
    // Вывод результатов
    //cout << "Решение системы:" << endl;
    //for (int i = 0; i < n; i++) {
    //    cout << "x" << i+1 << " = " << fixed << setprecision(2) << x[i] << endl;
    //}
    // (𝑥0, 𝑦0, 𝑧0) будут:
    double y[3];
    for (int i = 0; i < 3; i++) {
        y[i] = (-0.5)*x[i];
    }
    //ищем радиус в квадрате
    double r = pow(y[0],2)+pow(y[1],2)+pow(y[2],2) - x[3];
    // вывводим формулу 
    cout << fixed << setprecision(2) << "(x-" << y[0] << ")^2 + (y-"<< y[1] << ")^2 + (z-" << y[2] << ")^2 =" <<  r;
}