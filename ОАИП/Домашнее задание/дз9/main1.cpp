#include <iostream>
#include <memory> // Для использования std::unique_ptr
using namespace std;
int main(){
    unique_ptr<int> ptr = make_unique<int>(10);
    cout << *ptr << endl;
    *ptr = 25;
    cout << *ptr << endl;
}