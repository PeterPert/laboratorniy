#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

int main() {
    vector<vector<double>> temp(5, vector<double>(30));
    vector<vector<double>> pressure(5, vector<double>(100));
    
    // формула которая задает данные для списков
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 30; j++) {
            temp[i][j] = 20 + i * 5 + (j % 10) * 0.5;
        }
        for (int j = 0; j < 100; j++) {
            pressure[i][j] = 100 + i * 20 + (j % 15) * 1.5;
        }
    }
    
    // Средняя температура для каждого канала
    vector<double> avg_temp(5);
    transform(temp.begin(), temp.end(), avg_temp.begin(),
              [](const vector<double>& channel) {
                  return accumulate(channel.begin(), channel.end(), 0.0) / channel.size();
              });
    
    cout << "Средние температуры по каналам: ";
    for (double val : avg_temp) cout << val << " ";
    cout << endl;
    
    // Максимальное давление для каждого канала
    vector<double> max_pressure(5);
    transform(pressure.begin(), pressure.end(), max_pressure.begin(), // проходимся по pressure от нач до конца и берем как int x только теперь уже берем целый вектор и он как int становится привязанным к большому вектору
        [](vector<double>channel) { 
            return *max_element(channel.begin(), channel.end());
        });
    cout << "макс давление" << endl;
    for (int i = 0; i < 5; i++) {
        cout << max_pressure[i] << endl;
    }

    // Минимальное давление для каждого канала  
    vector<double> min_pressure(5);
    transform(pressure.begin(), pressure.end(), min_pressure.begin(),
        [](vector<double>channel) {
            return *min_element(channel.begin(), channel.end());
        });
    cout << "мин давление" << endl;
    for (int i = 0; i < 5; i++) {
        cout << min_pressure[i] << endl;
    }
    // Разности между соседними измерениями температуры
    vector<vector<double>> temp_diff(5, vector<double>(29));
    for (int i = 0; i < 5; i++) {
        transform(temp[i].begin(), temp[i].end() - 1, temp[i].begin() + 1, temp_diff[i].begin(),
                  [](double a, double b) { return abs(b - a); });
    }
    
    // Разности между соседними измерениями давления
    vector<vector<double>> pressure_diff(5, vector<double>(99));
    for (int i = 0; i < 5; i++) {
        transform(pressure[i].begin(), pressure[i].end() - 1, pressure[i].begin() + 1, pressure_diff[i].begin(),
                  [](double a, double b) { return abs(b - a); });
    }
    
    // Канал с наибольшей вариацией температуры
    vector<double> temp_variation(5);
    transform(temp.begin(), temp.end(), temp_variation.begin(),
              [](const vector<double>& channel) {
                  //auto [min_it, max_it] = minmax_element(channel.begin(), channel.end());
                auto it_min = min_element(channel.begin(), channel.end());
                auto it_max = max_element(channel.begin(), channel.end());
                return *it_max - *it_min;
              });
    
    auto max_var_it = max_element(temp_variation.begin(), temp_variation.end());
    cout << "макс вариация:" <<  *max_var_it << ")" << endl;
    
    // Нормализация давления для каждого канала
    vector<vector<double>> normalized_pressure(5, vector<double>(100));
    for (int i = 0; i < 5; i++) {
        double min_val = min_pressure[i];
        double max_val = max_pressure[i];
        double range = max_val - min_val;
        
        transform(pressure[i].begin(), pressure[i].end(), normalized_pressure[i].begin(),
                  [min_val, range](double val) { return (val - min_val) / range; });
    }
    
    // Вывод пиков давления после нормализации (> 0.9)
    cout << "Пики давления  > 0.9(нормализ):" << endl;
    for_each(normalized_pressure.begin(), normalized_pressure.end(),
            [](vector<double>channel) {
                for_each(channel.begin(), channel.end(),[](double val) {
                    if (val > 0.9) {
                        cout << val << " ";
                    }
                });
            });
    cout << endl;
    
    // Сортировка средних температур и поиск канала с максимальной
    vector<int> channel_indices(5);
    sort(avg_temp.begin(), avg_temp.end(), [](int a, int b) { return a < b; });
    auto im = max_element(avg_temp.begin(), avg_temp.end());
    for (int k = 0; k < 5; k++) {
        if (avg_temp[k] == *im) {
            cout << "индекс канал с max:" << k << endl;
        }
    }
    cout << endl;
}