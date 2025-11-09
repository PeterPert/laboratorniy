#include <iostream>
#include <iomanip>
using namespace std;

// Функция для выделения памяти под пластину
double **allocatePlate(int n, int m) {
    double **plate = new double*[n];
    for (int i = 0; i < n; ++i) {
        plate[i] = new double[m];
    }
    return plate;
}

// Функция для освобождения памяти
void freePlate(double **plate, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] plate[i];
    }
    delete[] plate;
}

// Функция обновления температуры
void updateTemperature(double **plate, int n, int m) {
    double **newPlate = allocatePlate(n, m);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Если это нагреватель в центре - сохраняем температуру
            int center_i = n / 2;
            int center_j = m / 2;
            if (i == center_i && j == center_j) {
                newPlate[i][j] = 100.0;
                continue;
            }
            // Вычисляем среднюю температуру соседей
            double sum = 0.0;
            int count = 0;
            // Верхний сосед
            if (i > 0) {
                sum += *(*(plate + i - 1) + j);
                count++;
            }
            // Нижний сосед
            if (i < n - 1) {
                sum += *(*(plate + i + 1) + j);
                count++;
            }
            // Левый сосед
            if (j > 0) {
                sum += *(*(plate + i) + j - 1);
                count++;
            }
            // Правый сосед
            if (j < m - 1) {
                sum += *(*(plate + i) + j + 1);
                count++;
            }
            if (count > 0) {
                *(*(newPlate + i) + j) = sum / count;
            } 
            else {
                *(*(newPlate + i) + j) = *(*(plate + i) + j);
            }
        }
    }
    
    // Копируем новые значения обратно в исходный массив
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            *(*(plate + i) + j) = newPlate[i][j];
        }
    }
    
    // Освобождаем временную память
    freePlate(newPlate, n);
}

int main() {
    int N, M, K;
    
    cout << "Введите размеры пластины (N M): ";
    cin >> N >> M;
    cout << "Введите количество итераций K: ";
    cin >> K;
    
    // Выделяем память под пластину
    double **plate = allocatePlate(N, M);
    
    // Инициализируем пластину
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            plate[i][j] = 20.0;  // начальная температура
        }
    }
    // Устанавливаем нагреватель в центре
    int center_i = N / 2;
    int center_j = M / 2;
    plate[center_i][center_j] = 100.0;

    //начальное
    cout << fixed << setprecision(2);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << setw(8) << *(*(plate + i) + j) << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Выполняем итерации
    for (int iter = 0; iter < K; ++iter) {
        updateTemperature(plate, N, M);
    }
    
    cout << "Финальное распределение температуры:" << endl;
    
    cout << fixed << setprecision(2);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << setw(8) << *(*(plate + i) + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // Освобождаем память
    freePlate(plate, N);
    return 0;
}