#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;
int main() {
    vector<int> numb = { 15, 8, 23, 4, 42, 19, 7, 31, 14, 28,
                                3, 37, 14, 25, 9, 33, 6, 21, 17, 12 };

    // Выводим исходный вектор
    cout << "Исходный вектор: ";
    for (int num : numb) {
        cout << num << " ";
    }
    cout << endl;
    auto it = find(numb.begin(), numb.end(), 7);
    if (it != numb.end())
        cout << "Элемент найден: " << *it << " на позиции " << (it - numb.begin()); 
    else
        cout << "Элемент не найден";
    cout << endl;
    sort(numb.begin(), numb.end());    
    numb.erase(unique(numb.begin(), numb.end()), numb.end());

    for (int num:numb) {
        cout << num << " ";
    }
}