#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int const n = 3;
    //cin >> n;
    int a[n][2];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> a[i][j];
        }
    }
    double cx = ((double)a[0][0]+a[1][0]+a[2][0])/3;
    double cy = ((double)a[0][1]+a[1][1]+a[2][1])/3;
    cout << "cx" << cx << endl;
    cout << "cy" << cy << endl;
    

}