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
    int* p = &vec[0];
    int sum = 0;
    while (*p != '\0') {
        sum += *p;
        p++;
    }
    cout << sum << endl;
}