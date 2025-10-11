#include <iostream>
#include <cmath>
using namespace std;
int main() {
	double x1, y1, x2, y2, x3, y3;
	cout << "введите коорд первой точки:";
	cin >> x1;
	cin >> y1;
	cout << "введите коорд второй точки:";
	cin >> x2;
	cin >> y2;
	cout << "введите коорд третей точки:";
	cin >> x3;
	cin >> y3;
	double S =0.5 * abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)));
	cout << "Площадь:" << S << endl;
}