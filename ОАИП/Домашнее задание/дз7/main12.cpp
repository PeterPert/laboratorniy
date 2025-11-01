#include <iostream> 
#include <cstring>
#include<vector>
using namespace std;
int main() {
    vector<int> vec;
    int len;
    int c;
    cin >> len;
    for (int i = 0; i < len; i++) {
        cin >> c;
        vec.push_back(c);
    }
    int* p = vec.data();
    while (*p != '\0') {
        *p += 10;
        p++;
    }
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}