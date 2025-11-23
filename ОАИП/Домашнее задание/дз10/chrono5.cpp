#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>

using namespace std;
using namespace std::chrono;

// Пузырьковая сортировка
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
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
    
    vector<int> leftArr(n1), rightArr(n2);
    
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Рекурсивная функция сортировки слиянием
void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Основная функция сортировки слиянием
void mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// Функция разделения для быстрой сортировки
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

// Рекурсивная функция быстрой сортировки
void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

// Основная функция быстрой сортировки
void quickSort(vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}

// Функция для генерации случайного массива
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 100000);
    
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

// Функция для измерения времени выполнения
template<typename Func>
long long measureSortingTime(Func sortFunc, vector<int> arr, const string& sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    
    long long timeMs = duration_cast<milliseconds>(end - start).count();
    
    // Проверка корректности сортировки
    if (!isSorted(arr)) {
        cout << "ОШИБКА: " << sortName << " работает некорректно!" << endl;
    }
    
    return timeMs;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    const int ARRAY_SIZE = 10000;
    const int NUM_TESTS = 3;
    
    cout << "=== СРАВНЕНИЕ АЛГОРИТМОВ СОРТИРОВКИ ===" << endl;
    cout << "Размер массива: " << ARRAY_SIZE << " элементов" << endl;
    cout << "Количество тестов: " << NUM_TESTS << endl;
    vector<long long> bubbleTimes, insertionTimes, mergeTimes, quickTimes, stdTimes;
    for (int test = 0; test < NUM_TESTS; test++) {
        cout << "\nТест " << (test + 1) << ":" << endl;
        cout << "Генерация случайного массива..." << endl;
        
        vector<int> originalArray = generateRandomArray(ARRAY_SIZE);
        
        // Измерение времени для каждого алгоритма
        long long bubbleTime = measureSortingTime(
            [](vector<int> arr) { bubbleSort(arr); }, 
            originalArray, "Пузырьковая сортировка"
        );
        bubbleTimes.push_back(bubbleTime);
        
        long long insertionTime = measureSortingTime(
            [](vector<int> arr) { insertionSort(arr); }, 
            originalArray, "Сортировка вставками"
        );
        insertionTimes.push_back(insertionTime);
        
        long long mergeTime = measureSortingTime(
            [](vector<int> arr) { mergeSort(arr); }, 
            originalArray, "Сортировка слиянием"
        );
        mergeTimes.push_back(mergeTime);
        
        long long quickTime = measureSortingTime(
            [](vector<int> arr) { quickSort(arr); }, 
            originalArray, "Быстрая сортировка"
        );
        quickTimes.push_back(quickTime);
        
        long long stdTime = measureSortingTime(
            [](vector<int> arr) { sort(arr.begin(), arr.end()); }, 
            originalArray, "std::sort"
        );
        stdTimes.push_back(stdTime);
        
        cout << "Пузырьковая: " << bubbleTime << " мс" << endl;
        cout << "Вставками: " << insertionTime << " мс" << endl;
        cout << "Слиянием: " << mergeTime << " мс" << endl;
        cout << "Быстрая: " << quickTime << " мс" << endl;
        cout << "std::sort: " << stdTime << " мс" << endl;
    }
    
    // Вывод средних результатов
    cout << "\n========================================" << endl;
    cout << "СРЕДНИЕ РЕЗУЛЬТАТЫ:" << endl;
    cout << "========================================" << endl;
    
    auto calculateAverage = [](const vector<long long>& times) {
        long long sum = 0;
        for (auto time : times) sum += time;
        return sum / times.size();
    };
    
    cout << "Пузырьковая сортировка: " << calculateAverage(bubbleTimes) << " мс" << endl;
    cout << "Сортировка вставками: " << calculateAverage(insertionTimes) << " мс" << endl;
    cout << "Сортировка слиянием: " << calculateAverage(mergeTimes) << " мс" << endl;
    cout << "Быстрая сортировка: " << calculateAverage(quickTimes) << " мс" << endl;
    cout << "Стандартная сортировка: " << calculateAverage(stdTimes) << " мс" << endl;
    cout << "\n========================================" << endl;
    return 0;
}