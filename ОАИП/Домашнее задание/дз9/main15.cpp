#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    vector<string> routes = { "Moscow-Berlin", "Berlin-Paris", "Paris-Rome", "Rome-Moscow" };
    shared_ptr<vector<string>> ptrRoutes = make_shared<vector<string>>(routes);
    auto countCity = [](const shared_ptr<vector<string>>& routesPtr, const string& city){
        int count = 0;
        for (const auto& route : *routesPtr) {
            if (route.find(city) != string::npos) {
                count++;
            }
        }
        return count;
    };
    
    auto sortByLength = [](shared_ptr<vector<string>>& routesPtr) {
        sort(routesPtr->begin(), routesPtr->end(), 
             [](const string& a, const string& b) {
                 return a.length() > b.length(); // по убыванию длины
             });
    };
    
    auto concat = [](const shared_ptr<vector<string>>& routesPtr) -> string {
        string result;
        for (int i = 0; i < routesPtr->size(); i++) {
            result += (*routesPtr)[i];
            if (i < routesPtr->size() - 1) {
                result += " -> ";
            }
        }
        return result;
    };
    
    // Вывод исходных данных
    cout << "Исходные маршруты: ";
    for (const auto& route : *ptrRoutes) {
        cout << route << " ";
    }
    cout << endl;
    
    // 1. Подсчет маршрутов с "Paris"
    int parisCount = countCity(ptrRoutes, "Paris");
    cout << "Количество маршрутов с \"Paris\": " << parisCount << endl;
    
    // 2. Сортировка маршрутов по длине
    sortByLength(ptrRoutes);
    cout << "Отсортированные маршруты: ";
    for (const auto& route : *ptrRoutes) {
        cout << route << " ";
    }
    cout << endl;
    
    // 3. Объединение маршрутов в одну строку
    string combinedRoute = concat(ptrRoutes);
    cout << "Общий маршрут: " << combinedRoute << endl;
    return 0;
}