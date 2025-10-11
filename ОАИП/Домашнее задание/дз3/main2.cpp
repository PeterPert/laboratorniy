#include <iostream>
using namespace std;
int main() {
    // Ввод размера матрицы
    int const matrixSize = 4;
    int matrix[matrixSize][matrixSize];

    // Ввод элементов матрицы
    cout << "Введите элементы матрицы " << matrixSize << "x" << matrixSize << ":" << endl;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            cin >> matrix[i][j];
        }
    }

    // Вычисляем эталонную сумму (первая строка)
    int targetSum = 0;
    for (int j = 0; j < matrixSize; j++) {
        targetSum += matrix[0][j];
    }

    bool isMagicSquare = true;

    // Проверяем суммы всех строк
    for (int i = 1; i < matrixSize; i++) {
        int rS = 0;
        for (int j = 0; j < matrixSize; j++) {
            rS += matrix[i][j];
        }
        if (rS != targetSum) {
            isMagicSquare = false;
            break;
        }
    }

    // Если строки совпадают, проверяем столбцы
    if (isMagicSquare) {
        for (int j = 0; j < matrixSize; j++) {
            int cS = 0;
            for (int i = 0; i < matrixSize; i++) {
                cS += matrix[i][j];
            }
            if (cS != targetSum) {
                isMagicSquare = false;
                break;
            }
        }
    }

    // Если строки и столбцы совпадают, проверяем главную диагональ
    if (isMagicSquare) {
        int mainDiagonalS = 0;
        for (int i = 0; i < matrixSize; i++) {
            mainDiagonalS += matrix[i][i];
        }
        if (mainDiagonalS != targetSum) {
            isMagicSquare = false;
        }
    }

    // Если всё ещё магический квадрат, проверяем побочную диагональ
    if (isMagicSquare) {
        int secondaryDiagonalS = 0;
        for (int i = 0; i < matrixSize; i++) {
            secondaryDiagonalS += matrix[i][matrixSize - 1 - i];
        }
        if (secondaryDiagonalS != targetSum) {
            isMagicSquare = false;
        }
    }

    // Вывод результата
    if (isMagicSquare==true) {
        cout << "YES " << targetSum << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}