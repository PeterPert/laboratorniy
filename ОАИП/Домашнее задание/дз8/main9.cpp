#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

double *forward(double **weights, double *inputs, int n, int m) {
    double* mas = new double[n];
    for (int i = 0; i < n; i++) {
        mas[i] = 0.;
        for (int j = 0; j < m; j++) {
            mas[i] += (weights[i][j] * (inputs[j]));
        }
    }
    return mas;
}

int main() {
    int n, m;
    cin >> n >> m;
    srand(time(0));
    
    double** weights = new double*[n];
    for (int i = 0; i < n; i++) {
        weights[i] = new double[m];
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            weights[i][j] = (rand() / (double)RAND_MAX) * 2.0 - 1.0;
        }
    }
    
    double* inputs = new double[m];
    for (int i = 0; i < m; i++) {
        cin >> inputs[i];
    }
    
    cout << endl;
    double* outputs = forward(weights, inputs, n, m);
    
    for (int i = 0; i < n; i++) {
        cout << outputs[i] << " ";
    }
    cout << endl;
    
    delete[] outputs;
    delete[] inputs;
    for (int i = 0; i < n; i++) {
        delete[] weights[i];
    }
    delete[] weights;
    
    return 0;
}