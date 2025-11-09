#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int sumElements(int **arr, int n, int m) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sum += *(*(arr + i) + j);
        }
    }
    return sum;
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
            cin >> array[i][j]; 
        }
    }
}