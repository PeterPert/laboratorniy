#include <iostream>
#include <memory> // Для использования std::unique_ptr
using namespace std;
int main() {
    shared_ptr<int> ptr1 = make_shared<int>(10);
    shared_ptr<int> ptr2 = ptr1;
    shared_ptr<int> ptr3 = ptr1;
    cout << "Счётчик ссылок: " << ptr1.use_count() << endl;
    ptr2.reset();
    cout << "Счётчик ссылок: " << ptr1.use_count() << endl;
}