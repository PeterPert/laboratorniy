#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cstdlib>
using namespace std;
using namespace std::chrono;
// Пузырьковая сортировка
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Сортировка вставками
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Вспомогательная функция для сортировки слиянием
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Сортировка слиянием
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

// Вспомогательная функция для быстрой сортировки
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Быстрая сортировка
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// Функция для измерения времени выполнения сортировки
template<typename Func>
long long measureTime(Func sortFunction, vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

// Функция для создания случайного массива
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 10000);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Функция для проверки отсортированности массива
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    const int ARRAY_SIZE = 10000;
    
    cout << "Генерация массива из " << ARRAY_SIZE << " случайных чисел..." << endl;
    vector<int> originalArray = generateRandomArray(ARRAY_SIZE);
    
    cout << "\nСравнение времени работы алгоритмов сортировки:\n";
    cout << "===============================================\n";
    
    // Тестирование пузырьковой сортировки
    cout << "Пузырьковая сортировка: ";
    long long bubbleTime = measureTime(bubbleSort, originalArray);
    cout << bubbleTime << " мс" << endl;
    
    // Тестирование сортировки вставками
    cout << "Сортировка вставками: ";
    long long insertionTime = measureTime(insertionSort, originalArray);
    cout << insertionTime << " мс" << endl;
    
    // Тестирование сортировки слиянием
    cout << "Сортировка слиянием: ";
    long long mergeTime = measureTime([](vector<int> arr) { mergeSort(arr); }, originalArray);
    cout << mergeTime << " мс" << endl;
    
    // Тестирование быстрой сортировки
    cout << "Быстрая сортировка: ";
    long long quickTime = measureTime([](vector<int> arr) { quickSort(arr); }, originalArray);
    cout << quickTime << " мс" << endl;
    
    // Тестирование стандартной сортировки
    cout << "Стандартная сортировка (std::sort): ";
    long long stdSortTime = measureTime([](vector<int> arr) { sort(arr.begin(), arr.end()); }, originalArray);
    cout << stdSortTime << " мс" << endl;
    return 0;
}