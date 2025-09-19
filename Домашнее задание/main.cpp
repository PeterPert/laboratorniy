#include <iostream>
using namespace std;
int main() {
	int a;
	cin >> a; //ввод числа 
	int b;
	b = a / 100; 
	setlocale(LC_ALL, "");
	wcout << b << L"метра" << "  ";
	int c;
	c = a - b * 100;
	setlocale(LC_ALL, "");
	wcout << c << L"сантиметра" << endl;
}