#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <numeric>
using namespace std;

int main() {
    int N;
    cout << "Введите количество измерений N: ";
    cin >> N;
    
    vector<double> signals(N);
    cout << "Введите " << N  << endl;
    for (int i = 0; i < N; i++) {
        cout << "Сигнал " << i + 1 << ": ";
        cin >> signals[i];
    }
    unique_ptr<double[]> signalsArray = make_unique<double[]>(N);

    for (int i = 0; i < N; i++) {
        signalsArray[i] = signals[i];
    }

    auto mean = [&](){
        return accumulate(signals.begin(), signals.end(), 0.0) / N;
    };
    
    auto normalize = [&]() {
        double maxVal = *max_element(signals.begin(), signals.end());
        transform(signals.begin(), signals.end(), signals.begin(), [maxVal](double x) { return x / maxVal; });
    };
    
    auto copyBack = [&]() {
        for (int i = 0; i < N; i++) {
            signalsArray[i] = signals[i];
        }
    };
    
    cout << "\nИсходные данные: ";
    for_each(signals.begin(), signals.end(), [](double x) { cout << x << " "; });
    cout << endl;
    
    double average = mean();
    cout << "Среднее значение: " << fixed << setprecision(2) << average << endl;
    
    normalize();
    copyBack();
    
    cout << "Нормализованные сигналы: ";
    for_each(signals.begin(), signals.end(), [](double x) { cout << fixed << setprecision(3) << x << " "; });
    cout << endl;
    return 0;
}