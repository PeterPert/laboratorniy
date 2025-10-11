#include <iostream>
using namespace std;
int main() {
	for (int i = 1; i <= 10; i++) {
		int a = 10;
		//setlocale(LC_ALL, "");
		if (i == 1) {
			setlocale(LC_ALL, "");
			wcout << i << L" тарелка стоит:" << a * i << endl;
		}
		else if (i > 1 and i < 5) {
			setlocale(LC_ALL, "");
			wcout << i << L" тарелки стоят:" << a * i << endl;
		}
		else {
			setlocale(LC_ALL, "");
			wcout << i << L" тарелок стоят:" << a * i << endl;
		}
	}
	return 0;
}