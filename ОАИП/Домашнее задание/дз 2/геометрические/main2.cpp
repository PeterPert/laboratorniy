#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
int main() {
	int n;
	cin >> n;
	vector<int> a = {};
	vector<int> b = {};
	double P = 0, d;
	double x, y;
	for (int i = 0; i < n; i++) {
		cout << "задайте координату";	
		cin >> x >> y;
		a.push_back(x);
		b.push_back(y);
	}
	int tempx = a[0];
	int tempy = b[0];
	for (int i = 0; i < n-1; i += 1) {
		d = sqrt(pow((a[i + 1] - a[i]), 2) + pow((b[i + 1] - b[i]), 2));
		P += d;
	}
	d = sqrt(pow((tempx - a[n-1]), 2) + pow((tempy - b[n-1]), 2));
	P += d;
	cout << "Периметр: " << P;
}
