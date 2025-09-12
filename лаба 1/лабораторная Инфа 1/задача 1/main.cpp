#include <iostream>
using namespace std;
int main() {
	float a;
	cin >> a;
	if (a < 50000) {
		setlocale(LC_ALL, "");
		wcout <<L"Ваш налог:" << a * 13 / 100 << endl;
	}
	else if (50001 < a and a < 100000) {
		setlocale(LC_ALL, "");
		wcout << L"Ваш налог:" << a * 20 / 100 << endl;
	}
	else if (a > 100001) {
		setlocale(LC_ALL, "");
		wcout << L"Ваш налог:" << a * 25 / 100 << endl;
	}
	return 0;
}
