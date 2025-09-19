#include <iostream>
using namespace std;
int main() {
	int a;
	cin >> a; 
	if (a < 18) {
		cout << "вам меньше 18 лет" << endl;
	}
	else if (a > 18 and a < 60) {
		cout << "вам от 18 до 60 лет" << endl;
	}
	else {
		cout << "вам больше 60 лет" << endl;
	}
}