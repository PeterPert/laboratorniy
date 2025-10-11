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
    double det = a[0][0]* (a[1][1]*a[2][2]-a[1][2]*a[2][1])-a[0][1]*(a[1][0]*a[2][2]-a[1][2]*a[2][0])+a[0][2]*(a[1][0]*a[2][1]-a[1][1]*a[2][0]);
    if (det == 0) {
        cout << "точки коллинеарны (yes)" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}