#include <iostream>
using namespace std;
int main() {
	int a;
	cin >> a;
	if (a % 3 == 0 and a % 5 == 0) {
		cout << a << " na 3 and 5" << endl;
	}
	else if (a % 3 == 0) {
		cout << a << " na 3" << endl;
	}
	else if (a % 5 == 0) {
		cout << a << " na 5" << endl;
	}
	else {
		cout << a << " ne 3 and 5" << endl;
	}
}

