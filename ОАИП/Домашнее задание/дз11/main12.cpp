#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

int main() {
    vector<int> numbers(100000);
    for (int i = 0; i < 100000; i++) {
        numbers[i] = i;
    }

    // Метод 1: По одному
    auto start1 = chrono::steady_clock::now();
    ofstream file1("test1.txt");
    for (int num : numbers) {
        file1 << num << " ";
    }
    file1.close();
    auto end1 = chrono::steady_clock::now();
    auto time1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);

    // Метод 2: Все сразу  
    auto start2 = chrono::steady_clock::now();
    ofstream file2("test2.txt");
    for (int num : numbers) {
        file2 << num << " ";
    }
    file2.close();
    auto end2 = chrono::steady_clock::now();
    auto time2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);

    cout << "Время записи по одному: " << time1.count() << " мс" << endl;
    cout << "Время записи всех сразу: " << time2.count() << " мс" << endl;

    return 0;
}