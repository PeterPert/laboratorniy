
#include <iostream>
using namespace std;
void bubbleSort(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				// Обмен элементов, если текущий больше следующего
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
int main() {
	const int size = 10; // Размер массива
	int numbers[size]; // Объявление массива
	int sum = 0; // Переменная для хранения суммы
	setlocale(LC_ALL, "");
	wcout << L"Введите " << size << L" целых чисел:" << endl;
	for (int i = 0; i < size; i++) {
		cin >> numbers[i];
		sum += numbers[i]; // Добавляем текущий элемент к сумме
	}
	setlocale(LC_ALL, "");
	wcout << L"Сумма всех элементов массива: " << sum << endl;
	for (int i = 0; i < size; i++) { //Выведите элементы массива на экран
		cout << numbers[i] << " ";
	}
	cout << " " << endl;
	// Поиск минимального элемента
	int minElement = numbers[0]; // Пусть первый элемент будет начальным минимумом
	for (int i = 1; i < size; i++) {
		if (numbers[i] < minElement) {
			minElement = numbers[i]; // Обновляем минимальный элемент, если находим более маленький
		}
	}
	setlocale(LC_ALL, "");
	wcout << L"Минимальный элемент массива: " << minElement << endl;
	// сортировка пузырьком
	bubbleSort(numbers, size);
	setlocale(LC_ALL, "");
	wcout << L"Отсортированный список: " << " ";
	for (int i = 0; i < size; i++) { //Выведите элементы массива на экран
		cout << numbers[i] << " ";
	}
	return 0;
}

