#include <iostream>
using namespace std;

class Shape {
public:
    double length;
};

class Rectangle : public Shape {
public:
    double width;
    
    Rectangle(double l, double w) {
        length = l;
        width = w;
    }
    
    double calculateArea() {
        return length * width;
    }
    
    double calculatePerimeter() {
        return 2 * (length + width);
    }
    
    void displayInfo() {
        cout << "Длина: " << length 
             << ", Ширина: " << width 
             << ", Площадь: " << calculateArea()
             << ", Периметр: " << calculatePerimeter();
    }
};

int main() {
    Rectangle rect(10, 5);
    rect.displayInfo();
    return 0;
}