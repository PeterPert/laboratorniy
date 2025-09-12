
#include <iostream>
using namespace std;
void bubbleSort(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				// ����� ���������, ���� ������� ������ ����������
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
int main() {
	const int size = 10; // ������ �������
	int numbers[size]; // ���������� �������
	int sum = 0; // ���������� ��� �������� �����
	setlocale(LC_ALL, "");
	wcout << L"������� " << size << L" ����� �����:" << endl;
	for (int i = 0; i < size; i++) {
		cin >> numbers[i];
		sum += numbers[i]; // ��������� ������� ������� � �����
	}
	setlocale(LC_ALL, "");
	wcout << L"����� ���� ��������� �������: " << sum << endl;
	for (int i = 0; i < size; i++) { //�������� �������� ������� �� �����
		cout << numbers[i] << " ";
	}
	cout << " " << endl;
	// ����� ������������ ��������
	int minElement = numbers[0]; // ����� ������ ������� ����� ��������� ���������
	for (int i = 1; i < size; i++) {
		if (numbers[i] < minElement) {
			minElement = numbers[i]; // ��������� ����������� �������, ���� ������� ����� ���������
		}
	}
	setlocale(LC_ALL, "");
	wcout << L"����������� ������� �������: " << minElement << endl;
	// ���������� ���������
	bubbleSort(numbers, size);
	setlocale(LC_ALL, "");
	wcout << L"��������������� ������: " << " ";
	for (int i = 0; i < size; i++) { //�������� �������� ������� �� �����
		cout << numbers[i] << " ";
	}
	return 0;
}

