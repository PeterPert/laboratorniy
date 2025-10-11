#include <iostream>
using namespace std;
int main() {
	cout << "x+y+z=6" << endl;
	cout << "2x−y+3z=14" << endl;
	cout << "−x+4y−z=2" << endl;
	double m[3][4] = {
		{1, 1, 1, 6},
		{2, -1, 3, 14},
		{-1, 4, -1, 2}
	};
	double a[4] = { 1, 1, 1, 6 };
	for (int i = 0; i < 4; i++) {
		m[1][i] = m[1][i] - a[i] * 2;
		m[2][i] = m[2][i] + a[i];
	}
	for (int i = 0; i < 4; i++) {
		m[2][i] = m[2][i] + (5 * m[1][i])/3;
	}
	for (int i = 0; i < 3; i++) {
		cout << endl;
		for (int j = 0; j < 4; j++) {
			cout << m[i][j];
		}
	}
	cout << endl;
	double z = m[2][3] / m[2][2];
	double y =  -0.6666667 + (z / 3);
	double x = 6 - y - z;
	cout << "x" << x << endl;
	cout << "y" << y << endl;
	cout << "z" << z << endl;
}