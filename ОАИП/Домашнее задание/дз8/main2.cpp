#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
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
            array[i][j] = rand() % 100; 
        }
    }
    cout << "Двумерный массив:\n"; 
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) { 
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

