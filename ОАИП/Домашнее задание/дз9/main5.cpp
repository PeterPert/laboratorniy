#include <iostream>
#include <memory> // Для использования std::unique_ptr
using namespace std;
int main() {
    int n , m;
    cout << "введите размеры массива" << endl;
    cin >> n;
    cin >> m;
    unique_ptr<int[]> arr = make_unique<int[]>(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i * m + j] = i * j;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << endl;
        for (int j = 0; j < m; j++) {
            cout << arr[i * m + j]<< " ";
        }
    }
}