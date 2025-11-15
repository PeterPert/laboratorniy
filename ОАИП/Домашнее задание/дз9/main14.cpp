#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <numeric>
using namespace std;
int main(){
    int N, M;
    cout << "введите размеры матрицы: " << endl;
    cin >> N >> M;
    unique_ptr<double[]> matrix(new double[N*M]);
    for (int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> matrix[i * M + j];
        }
    }
    // Вывод матрицы для проверки
    cout << "\nВведенная матрица:" << endl;
    for (int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << setw(8) << matrix[i * M + j] << " ";
        }
        cout << endl;
    }
    auto sumColumns = [&](){vector<double>res(M, 0.0);// если мы не заполним вектор нулями то в дальнейшем будем проходиться по пустому вектору
        for (int j = 0; j < M; j++){
            double sum = 0;
            for (int i = 0; i < N; i++){  
                sum += matrix[i * M + j];  
            }
            res[j] = sum;
        }
        return res;
    };

    auto maxIndex = [](const vector<double>& v){
        int maxIdx = 0;
        double maxVal = v[0];
        for (int i = 1; i < v.size(); i++){
            if (v[i] > maxVal) {
                maxVal = v[i];
                maxIdx = i;
            }
        }
        return maxIdx;
    };
    
    vector<double>summer = sumColumns();
    int maxIdx = maxIndex(summer);

    for (double sum : summer) {
        cout << fixed << setprecision(2) << setw(8) << sum << " ";
    }
    cout << endl;
    
    cout << "Максимальная сумма: " << fixed << setprecision(2) << summer[maxIdx]  << " (столбец " << maxIdx << ")" << endl;
}