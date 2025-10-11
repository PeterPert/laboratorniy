#include <iostream>
using namespace std; 
int main() {
	int n; 
	cout << "Введите количество элементов массива: ";
	cin >> n;
	int* array = new int[n];
	int k = 0, m = 0;
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}
	for (int i = 0; i < n; i++) {
		if (array[i] > pow(2, i)) {
			m++;
		}
	}
	cout << m << endl;
	return 0;
}	

	
		