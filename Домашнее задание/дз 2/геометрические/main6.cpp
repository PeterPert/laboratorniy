#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int h = 0;
    int const n = 4;
    int a[n][2];
    for (int i = 0; i < n; i++) { // ввод списка
        for (int j = 0; j < 2; j++) {
            if (h == 4) {
                cout << "Введите координаты нового вектора " << endl;
            }
            cin >> a[i][j];
            h += 1;
        }
    }

    int g = 0; // если 0, то не пересек ; если 1, то пересекаются

    
    double o1 = (a[1][0] - a[0][0]) * (a[2][1] - a[0][1]) - (a[1][1] - a[0][1]) * (a[2][0] - a[0][0]);
    double o2 = (a[1][0] - a[0][0]) * (a[3][1] - a[0][1]) - (a[1][1] - a[0][1]) * (a[3][0] - a[0][0]);
    double o3 = (a[3][0] - a[2][0]) * (a[0][0] - a[2][1]) - (a[3][1] - a[2][1]) * (a[0][0] - a[2][0]);
    double o4 = (a[3][0] - a[2][0]) * (a[1][0] - a[2][1]) - (a[3][1] - a[2][1]) * (a[1][0] - a[2][0]);
    cout << o1 << endl;
    cout << o2 << endl;
    cout << o3 << endl;
    cout << o4 << endl;

    if (o1*o2<= 0 and o3*o4<=0) {
            g = 1;
    }
    if (g == 1) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
}