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

    for (int i = 0; i < 3; i++) { //проверка на одинак коорд 
        if (a[i][0] == a[i + 1][0] and a[i][1] == a[i + 1][1]) {
            g = 1;
        }
        else if (a[0][0] == a[3][0] and a[0][1] == a[3][1]) {
            g = 1;
        }
    }

    if (g == 1) {
        cout << "yes" << endl;
    }
    else { //проверка на 3 точки в линию
        double o1 = (a[1][0] - a[0][0]) * (a[2][1] - a[0][1]) - (a[1][1] - a[0][1]) * (a[2][0] - a[0][0]);
        double o2 = (a[1][0] - a[0][0]) * (a[3][1] - a[0][1]) - (a[1][1] - a[0][1]) * (a[3][0] - a[0][0]);
        double o3 = (a[3][0] - a[2][0]) * (a[0][0] - a[2][1]) - (a[3][1] - a[2][1]) * (a[0][0] - a[2][0]);
        double o4 = (a[3][0] - a[2][0]) * (a[1][0] - a[2][1]) - (a[3][1] - a[2][1]) * (a[1][0] - a[2][0]);
        cout << o1 << endl;
        cout << o2 << endl;
        cout << o3 << endl;
        cout << o4 << endl;

        if (o1 == 0 or o2 == 0 or o3 == 0 or o4 == 0) {
            g = 0;
        }
        else { // проверка на коллинеарность 
            if ((a[1][0] - a[0][0]) * (a[3][1] - a[2][1]) == (a[3][0] - a[2][0]) * (a[1][1] - a[0][1])) {
                g = 0;
            }
            else {
                g = 1;
            }
        }

        if (g == 1) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }

    }
}