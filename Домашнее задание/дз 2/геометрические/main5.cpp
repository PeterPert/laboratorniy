#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int const n = 3;
    int a[n][2];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> a[i][j];
        }
    }
    double d;
    if ((a[1][0] - a[0][0]) * (a[2][1] - a[0][1]) - (a[1][1] - a[0][1]) * (a[2][0] - a[0][0]) == 0) {
        cout << "yes" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}
