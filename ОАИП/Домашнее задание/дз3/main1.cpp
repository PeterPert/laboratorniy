#include <iostream>
using namespace std;
int main() {
	const int rows = 4;
	const int cols = 4;
	int matrix[rows][cols];
	int matrix1[rows][cols];
	int matrix2[rows][cols];
	int matrix3[rows][cols];
	int matrix4[rows][cols];
	// Ввод элементов матрицы
	cout << "Введите элементы матрицы 3x3:" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> matrix[i][j];
		}
	}
	//отражение относительно главной диагонали 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix1[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix1[i][j] = matrix1[j][i];
		}
	}

	//отражение относительно побочной диагонали 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix2[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix2[rows - j-1][cols - i-1] = matrix2[i][j];
		}
	}

	//зеркальное отражение относительно вертикальной оси
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix3[i][j] = matrix[i][j];
		}
	}

	if (cols % 2 == 0) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols / 2; j++) {
				matrix3[i][cols - j - 1] = matrix3[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols / 2; j++) {
				if (j == (cols + 1) / 2) {
					continue;
				}
				else {
					matrix3[i][cols - j - 1] = matrix3[i][j];
				}
			}
		}
	}

	//зеркальное отражение относительно горизонтальной оси (верх↔низ). Затем сравните эти четыре матрицы попарно и выведите, какие из них совпадают.
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix4[i][j] = matrix[i][j];
		}
	}

	if (rows % 2 == 0) {
		for (int i = 0; i < rows/2; i++) {
			for (int j = 0; j < cols; j++) {
				matrix4[rows-i-1][j] = matrix4[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < rows/2; i++) {
			for (int j = 0; j < cols; j++) {
				if (j == (rows + 1) / 2) {
					continue;
				}
				else {
					matrix4[rows-i-1][cols] = matrix4[i][j];
				}
			}
		}
	}


	// Вывод матрицы1
	cout << "Матрица1:" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix1[i][j] << " ";
		}
		cout << endl;
	}

	// Вывод матрицы2
	cout << "Матрица2:" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix2[i][j] << " ";
		}
		cout << endl;
	}

	// Вывод матрицы3
	cout << "Матрица3:" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix3[i][j] << " ";
		}
		cout << endl;
	}

	// Вывод матрицы4
	cout << "Матрица4:" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix4[i][j] << " ";
		}
		cout << endl;
	}

	// Вывод матрицы (вспомогательный)
	cout << "Матрица:" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}