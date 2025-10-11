#include <iostream>
using namespace std;
int main() {
	int a[3][3];
	for (int i = 0; i < 3; i++) {
		int h = 0;
		cout << "new" << endl;
		for (int j = 0; j < 3; j++) {
			if (h == 2) {
				a[i][j] = 1;
			}
			else {
				h += 1;
				cin >> a[i][j];
			}
		}
	}
	double s = 0.5 * abs(a[0][0] * (a[1][1] * a[2][2] - a[1][2] * a[2][1])
		- a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0])
		+ a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]));
	for (int i = 0; i < 3; i++) {
		cout << endl;
		for (int j = 0; j < 3; j++) {
			cout << a[i][j];
		}
	}
	cout << "" << endl;
	cout << s << endl;
	return 0;
}