#include <iostream>
#include <memory> // Для использования std::unique_ptr
using namespace std;
int main() {
    unique_ptr<int> ptr1 = make_unique<int>(42);
    unique_ptr<int> ptr2 = move(ptr1);
    if (ptr1) {
        cout << "ptr1: " << *ptr1 << endl;
    } else {
        cout << "ptr1: nullptr" << endl;
    }
    if (ptr2) {
        cout << "ptr2: " << *ptr2 << endl;
    } else {
        cout << "ptr2: nullptr" << endl;
    }
    return 0;
}
