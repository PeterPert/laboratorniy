#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    vector<double> temperatures;
    ifstream inFile("sensor_data.txt");
    double temp;
    
    while (inFile >> temp) {
        temperatures.push_back(temp);
    }
    inFile.close();
    
    // Удаляем некорректные значения
    temperatures.erase(
        remove_if(temperatures.begin(), temperatures.end(), [](double t) {
        return t < -50.0 || t > 50.0;
    }),temperatures.end());
    
    // Вычисление средней температуры
    if (!temperatures.empty()) {
        double sum = accumulate(temperatures.begin(), temperatures.end(), 0.0);
        double average = sum / temperatures.size();
        cout << "Средняя температура: " << average << "°C" << endl;
    }
    
    ofstream outFile("filtered_data.txt");
    outFile << "Отфильтрованные данные температуры:\n";
    for (double t : temperatures) {
        outFile << t << "\n";
    }
    outFile.close();
    return 0;
}