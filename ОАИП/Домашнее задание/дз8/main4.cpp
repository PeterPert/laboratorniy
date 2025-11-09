#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int **transpose(int **matrix, int n, int m) {
    int** result = new int*[m];
    for (int i = 0; i < m; ++i) {
        result[i] = new int[n];
    }
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = matrix[j][i];  // Меняем индексы местами
        }
    }
    return result;
}

int main() {
    srand(time(0));
    int rows;
    cin >> rows;
    int cols;
    cin >> cols;
    int** array = new int*[rows]; 
    for (int i = 0; i < rows; ++i) {
        array[i] = new int[cols]; 
    }
    for (int i = 0; i < rows; ++i) { 
        for (int j = 0; j < cols; ++j) {
            array[i][j] = rand() % 100; 
        }
    }
    
    // Вывод исходной матрицы
    cout << "Исходная матрица " << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    
    // Транспонирование
    int** transposed = transpose(array, rows, cols);
    cout << "\nТранспонированная матрица " << endl;
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            cout << transposed[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

