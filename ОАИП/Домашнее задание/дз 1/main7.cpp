#include <iostream>
using namespace std;
int main() {
	int a, b;
	cin >> a;
	int i = 1;
	while (i < a+1) {
		b = pow(i, 2);
		cout << b << endl;
		i++;
	}
}
