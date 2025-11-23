#include <iostream>
#include <chrono>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    long long total_seconds;
    cout << "Введите количество секунд: ";
    cin >> total_seconds;
    chrono::seconds total_duration(total_seconds);
    auto hours = chrono::duration_cast<chrono::hours>(total_duration);
    auto remaining_after_hours = total_duration - hours;
    auto minutes = chrono::duration_cast<chrono::minutes>(remaining_after_hours);
    auto seconds = remaining_after_hours - minutes;
    long long h = hours.count();
    long long m = minutes.count();
    long long s = seconds.count();
    if (h > 0) {
        if (h == 1) cout << h << " час ";
        else if (h >= 2 && h <= 4) cout << h << " часа ";
        else cout << h << " часов ";
    }
    if (m > 0) {
        if (m == 1) {
            cout << m << " минута ";
        }
        else if (m >= 2 && m <= 4) {
            cout << m << " минуты ";
        }
        else {
            cout << m << " минут ";
        }
    }
    if (s > 0 || (h == 0 && m == 0)) {
        if (s == 1) {
            cout << s << " секунда";
        }
        else if (s >= 2 && s <= 4) {
            cout << s << " секунды";
        }
        else {
            cout << s << " секунд";
        }
    }
    cout << endl;
    return 0;
}