#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Функция для вычисления средней нагрузки каждого узла
double* averageLoadPerNode(int** load, int n, int t) {
    double* averages = new double[n];
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < t; j++) {
            sum += *(*(load + i) + j);  
        }
        averages[i] = sum / t;
    }
    return averages;
}

// Функция для нормализации нагрузки
void normalizeLoad(int** load, int n, int t) {
    double* averages = averageLoadPerNode(load, n, t);
    
    for (int i = 0; i < n; i++) {
        if (averages[i] > 80) {
            for (int j = 0; j < t; j++) {
                if (*(*(load + i) + j) > 80) {
                    int amount = round(*(*(load + i) + j) * 0.1);
                    *(*(load + i) + j) -= amount;
                    int perNode = amount / (n - 1);
                    int remainder = amount % (n - 1);
                    
                    for (int k = 0; k < n; k++) {
                        if (k != i) {
                            *(*(load + k) + j) += perNode;
                            
                            if (remainder > 0) {
                                *(*(load + k) + j) += 1;
                                remainder--;
                            }
                            
                            if (*(*(load + k) + j) > 100) {
                                *(*(load + k) + j) = 100;
                            }
                        }
                    }
                }
            }
        }
    }
    
    delete[] averages;
}
// Функция для нахождения критического интервала
int findCriticalInterval(int** load, int n, int t) {
    int maxSum = 0;
    int criticalInterval = 0;
    
    for (int j = 0; j < t; j++) {
        int currentSum = 0;
        for (int i = 0; i < n; i++) {
            currentSum += *(*(load + i) + j);  
        }
        if (currentSum > maxSum) {
            maxSum = currentSum;
            criticalInterval = j;
        }
    }
    
    return criticalInterval;
}

// Функция для красивого вывода матрицы
void printMatrix(int** load, int n, int t) {
    cout << "Матрица нагрузок:" << endl;
    cout << "     ";
    for (int j = 0; j < t; j++) {
        cout << "T" << j << "  ";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "Уз" << i << "  ";
        for (int j = 0; j < t; j++) {
            cout << setw(3) << *(*(load + i) + j) << " ";
        }
        cout << endl;
    }
}

// Функция для выделения памяти под матрицу
int** allocateMatrix(int n, int t) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[t];
    }
    return matrix;
}

// Функция для освобождения памяти
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    int N, T;
    
    cout << "Введите количество узлов и интервалов: ";
    cin >> N >> T;
    int** load = allocateMatrix(N, T);
    cout << "Введите нагрузку для каждого узла по интервалам:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "Узел " << i << ": ";
        for (int j = 0; j < T; j++) {
            cin >> load[i][j];
            if (load[i][j] < 0 || load[i][j] > 100) {
                cout << "Ошибка: нагрузка должна быть в диапазоне 0-100%" << endl;
                j--; 
            }
        }
    }
    
    // Вывод исходных данных
    cout << "\n=== Исходные данные ===" << endl;
    printMatrix(load, N, T);

    double* averages = averageLoadPerNode(load, N, T);
    cout << "\nСредняя нагрузка на узлах:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "Узел " << i << ": " << fixed << setprecision(2) << averages[i] << "%" << endl;
    }
    // Нормализация нагрузки
    normalizeLoad(load, N, T);
    // Вывод результатов после нормализации
    cout << "\n=== После нормализации ===" << endl;
    printMatrix(load, N, T);
    
    // Нахождение критического интервала
    int criticalInterval = findCriticalInterval(load, N, T);
    int totalLoad = 0;
    for (int i = 0; i < N; i++) {
        totalLoad += load[i][criticalInterval];
    }
    
    cout << "\nКритический интервал: " << criticalInterval 
         << " (суммарная нагрузка = " << totalLoad << "%)" << endl;
    
    delete[] averages;
    averages = averageLoadPerNode(load, N, T);
    cout << "\nСредняя нагрузка после нормализации:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "Узел " << i << ": " << fixed << setprecision(2) << averages[i] << "%" << endl;
    }
    
    // Освобождение памяти
    delete[] averages;
    freeMatrix(load, N);
    
    return 0;
}