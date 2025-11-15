#include <iostream>
#include <memory> // Для использования std::unique_ptr
using namespace std;
int main(){
    int n;
    cout << "введите длину массива" << endl;
    cin >> n;
    unique_ptr<int[]> arr = make_unique<int[]>(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
