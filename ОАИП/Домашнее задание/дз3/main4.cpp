#include <iostream>
using namespace std;
int main() {
    // Ввод размера матрицы
    int const m = 5;
    int matrix[m][m];
    int h = 0;
    for (int j = 0; j < m / 2; j++) {
        for (int i = h; i < m - h; i++) {
            cin >> matrix[h][i];
        }
        for (int i = h + 1; i < m - h; i++) {
            cin >> matrix[i][m - 1 - h];
        }
        for (int i = h + 1; i < m - h; i++) {
            cin >> matrix[m - 1 - h][m - i - 1];
        }
        for (int i = h + 1; i < m - h - 1; i++) {
            cin >> matrix[m - i - 1][m - (m - h)];
        }
        h++;
    }
    if (m % 2 != 0) {
        cin >> matrix[m / 2][m / 2];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}