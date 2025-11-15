#include <iostream>
#include <memory> // Для использования std::unique_ptr
using namespace std;
void fillArray(unique_ptr<int[]>& arr, int n){
    for (int i = 0; i < n; i++){
        arr[i] = i*i;
    }
    for (int i = 0; i < n; i++){
        cout << arr[i];
    }
}
int main(){
    int n = 3;
    unique_ptr<int[]> arr = make_unique<int[]>(n);
    fillArray(arr,n);
}