#include <iostream>
#include <cmath>
using namespace std;
struct Circle {
    double radius;
};

struct Rectangle {
    double length;
    double width;
};

union Shape {
    Circle circle;
    Rectangle rectangle;
};

int main() {
    Shape shape;
    int choice;
    const double PI = 3.14159265358979323846;
    cout << "Выберите фигуру (1 - круг, 2 - прямоугольник): ";
    cin >> choice;
    if (choice == 1) {
        cout << "Введите радиус круга: ";
        cin >> shape.circle.radius;
        double area = PI * shape.circle.radius * shape.circle.radius;
        cout << "Площадь круга: " << area << endl;
    }
    else if (choice == 2) {
        cout << "Введите длину прямоугольника: ";
        cin >> shape.rectangle.length;
        cout << "Введите ширину прямоугольника: ";
        cin >> shape.rectangle.width;
        double area = shape.rectangle.length * shape.rectangle.width;
        cout << "Площадь прямоугольника: " << area << endl;
    }
    else {
        cout << "Неверный выбор!" << endl;
        return 1;
    }
    return 0;
}