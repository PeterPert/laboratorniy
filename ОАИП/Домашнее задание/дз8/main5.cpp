#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int rowSum(int* row, int cols) {
    int sum = 0;
    for (int j = 0; j < cols; ++j) {
        sum += row[j];
    }
    return sum;
}

// Функция для сортировки строк по сумме элементов
void sortRowsBySum(int** arr, int rows, int cols) {
    int* sums = new int[rows];
    for (int i = 0; i < rows; ++i) {
        sums[i] = rowSum(arr[i], cols);
    }

    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < rows - i - 1; ++j) {
            if (sums[j] > sums[j + 1]) {
                // Меняем местами указатели на строки
                int* tempPtr = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tempPtr;
                
                // Меняем местами суммы
                int tempSum = sums[j];
                sums[j] = sums[j + 1];
                sums[j + 1] = tempSum;
            }
        }
    }
    
    delete[] sums;
}

int main() {
    srand(time(0));
    int rows, cols;
    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;
    
    // Создание двумерного массива
    int** arr = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        arr[i] = new int[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = rand() % 100;
        }
    }
    
    // Вывод исходного массива
    cout << "\nИсходный массив:" << endl;
    for (int i = 0; i < rows; ++i) {
        cout << "Строка " << i << " (сумма: " << rowSum(arr[i], cols) << "): ";
        for (int j = 0; j < cols; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    
    // Сортировка строк по сумме элементов
    sortRowsBySum(arr, rows, cols);
    
    // Вывод отсортированного массива
    cout << "\nОтсортированный массив:" << endl;
    for (int i = 0; i < rows; ++i) {
        cout << "Строка " << i << " (сумма: " << rowSum(arr[i], cols) << "): ";
        for (int j = 0; j < cols; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    // Освобождение памяти
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}