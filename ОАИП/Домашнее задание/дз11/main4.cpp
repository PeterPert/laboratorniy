#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int numbers[] = {15, 23, 7, 42, 18, 91, 3, 56, 77, 10};
    int count = 10;
    
    ofstream out("numbers.bin", ios::binary);
    out.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
    out.close();
    
    ifstream in("numbers.bin", ios::binary);
    
    in.seekg(0, ios::end);
    int size = in.tellg();
    in.seekg(0, ios::beg);
    
    int buffer[10];
    in.read(reinterpret_cast<char*>(buffer), size);
    in.close();
    
    cout << "Размер файла: " << size << " байт" << endl;
    int numbers_read = size / sizeof(int);
    int sum = 0;
    for (int i = 0; i < numbers_read; i++) {
        sum += buffer[i];
    }
    cout << endl << "Сумма: " << sum << endl;
    return 0;
}