#include <iostream>
#include <math.h>
using namespace std;
int main() {
	cout << "Введите первую координату" << endl;
	int x1, y1;
	int x2, y2;
	cin >> x1 >> y1;
	cin >> x2 >> y2;
	int dx = x1 - x2;
	int dy = y1 - y2;
	double d = sqrt(pow(dx, 2) + pow(dy, 2));
	cout << d << endl;
}