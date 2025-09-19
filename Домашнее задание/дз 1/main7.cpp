#include <iostream>
using namespace std;
int main() {
	int a, b;
	cin >> a;
	int i = 1;
	while (i < a) {
		b = pow(i, 2);
		cout << b << endl;
		i++;
	}
}