#include <iostream>
#include <memory> // Для использования std::unique_ptr
using namespace std;
double sred(unique_ptr<double[]>& arr, int m){
    double sum = 0;
    for (int i = 0; i < m; i++) {
        sum += arr[i];
    }
    return sum/m;
}

int main() {
    int n;
    cout << "укажите размер массива" << endl;
    cin >> n;
    double t, d, v;
    unique_ptr<double[]>temp = make_unique<double[]>(n);
    unique_ptr<double[]>davl = make_unique<double[]>(n);
    unique_ptr<double[]>vlag = make_unique<double[]>(n);
    for (int i = 0; i < n; i++){
        int tem;
        cout << "введите значения для температуры" <<endl;
        cin >> tem;
        temp[i] = tem;
    }
    for (int i = 0; i < n; i++){
        int dav;
        cout << "введите значения для давления" <<endl;
        cin >> dav;
        davl[i] = dav;
    }
    for (int i = 0; i < n; i++){
        int vl;
        cout << "введите значения для температуры" <<endl;
        cin >> vl;
        vlag[i] = vl;
    }
    t = sred(temp,n);
    d = sred(davl,n);
    v = sred(vlag,n);
    cout << "Параметр" << "\t" << "Среднее значаение"<< endl;
    cout << "Температура" << "\t" << t << endl;
    cout << "давление" << "\t" << d << endl;
    cout << "влажность" << "\t" << v << endl;
}