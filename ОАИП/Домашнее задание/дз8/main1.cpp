#include <iostream>
using namespace std;

void swapPointers(int** a, int** b) {
    int* temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x;
    cin >> x;
    int y;
    cin >> y;
    int* p1 = &x;
    int* p2 = &y;
    swapPointers(&p1, &p2);
    
    cout << "После обмена:" << endl;
    cout << *p1 << endl;
    cout << *p2 << endl;
    
    return 0;
}