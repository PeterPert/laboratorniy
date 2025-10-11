#include <iostream>
using namespace std;
int main() {
    int const n = 5;//колво столбцов
    int const m = 4;//колво строчек
    int a[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    int h = 0;
    int max = 0;
    if (n > m) {
        max = n;
    }
    else {
        max = m;
    }
    for (int i = 0; i < m; i++) {
        cout << " " << endl;
        for (int j = 0; j < n; j++) {
            cout << a[i][j];
        }
    }
    cout << " " << endl;
    cout << "------------------" << endl;
    for (int j = 0; j < max+1 / 2; j++) {
        int y = 0, b = 0, c = 0, d = 0;
        for (int i = h; i < n - h; i++) {
            cout << a[h][i];
            y += 1;
        }
        if (y == 0) {
            break;
        }
        
        for (int i = h + 1; i < m - h; i++) {
            cout << a[i][n - 1 - h];
            b += 1;
        }
        if (b == 0) {
            break;
        }

        for (int i = h + 1; i < n - h; i++) {
            cout << a[m - 1 - h][n - i - 1];
            c += 1;
        }
        if (c == 0) {
            break;
        }

        for (int i = h + 1; i < m - h - 1; i++) {
            cout << a[m - i - 1][m - (m - h)];
            d += 1;
        }
        if (d == 0) {
            break;
        }
        h++;
    }
}