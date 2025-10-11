#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x, y, theta;
    
    // Ввод координат точки и угла поворота
    cout << "Введите координаты точки (x y): ";
    cin >> x >> y;
    cout << "Введите угол поворота в градусах: ";
    cin >> theta;
    // Преобразование градусов в радианы
    double theta_rad = theta * M_PI/ 180.0;

    double cos_theta = cos(theta_rad);
    double sin_theta = sin(theta_rad);
    
    // Умножение матрицы на вектор (поворот точки)
    double x_new = x * cos_theta + y * sin_theta;
    double y_new = -x * sin_theta + y * cos_theta;
    
    cout << x << y << endl;
    cout << "Угол поворота: " << theta << " градусов" << endl;
    cout << "Повернутая точка: (" << x_new << ", " << y_new << ")" << endl;
    
    return 0;
}