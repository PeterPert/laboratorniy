#include <iostream>
#include <memory> 
#include <vector>
using namespace std;
unique_ptr<int[]> createArray(int n){
    unique_ptr<int[]>arr = make_unique<int[]>(n);
    for (int i = 0; i < n; i++){
        arr[i] = i;
    }
    return arr;
}

int main(){
    int s;
    cout << "введите размер массива" << endl;
    cin >> s;
    unique_ptr<int[]>array = createArray(s);
    for (int i = 0; i < s; i++){
        cout << array[i] << " ";
    }
}