#include <iostream>
#include <cstring>
using namespace std;
int main() {
    const int max_s = 100;
    char str[max_s];
    char sequences[max_s][max_s]; //[MAX_SIZE] - максимальное количество различных подстрок[MAX_SIZE] - максимальная длина каждой подстроки
    int count = 0;
    cin.getline(str, max_s);
    int n;
    cin >> n;
    int len = strlen(str);
    for (int i = 0; i < len - n + 1; i++) { //len - n+1 потому что дальше не тсмысла проверять 
        char temp[max_s];
        for (int j = 0; j < n; j++) {
            temp[j] = str[i + j];
        }
        temp[n] = '\0';
        int f = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(sequences[j], temp) == 0) {
                f = 1; 
                break;
            }
        }
        
        if (f == 0) {
            strcpy(sequences[count], temp);
            count++;
        }
    }
    
    for (int i = 0; i < count; i++) {
        cout << sequences[i] << " ";
    }
}