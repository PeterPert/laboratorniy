#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int const n = 4;
    double a[n][2];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> a[i][j];
        }
    }
    double tempx = a[0][0];
    double tempy = a[0][1];
    double max = 0;
    for (int i = 1; i < n; i++) {
        double d = sqrt((double)pow((tempx - a[i][0]), 2) + (double)pow((tempy - a[i][1]), 2));
        if (d > max) {
            max = d;
        }
    }
    cout << max << endl;

}