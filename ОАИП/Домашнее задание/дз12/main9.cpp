#include <iostream>
using namespace std;
union DateTime {
    struct Date {
        int year;
        int month;
        int day;
    } date;
    
    struct Time {
        int hour;
        int minute;
        int second;
    } time;
};
int main() {
    DateTime dt;
    cout << "Введите год: ";
    cin >> dt.date.year;
    cout << "Введите месяц: ";
    cin >> dt.date.month;
    cout << "Введите день: ";
    cin >> dt.date.day;
    cout << "Введите час: ";
    cin >> dt.time.hour;
    cout << "Введите минуту: ";
    cin >> dt.time.minute;
    cout << "Введите секунду: ";
    cin >> dt.time.second;
    cout << "Дата и время: " 
        << dt.date.year << "-" << dt.date.month << "-" << dt.date.day << " "
        << dt.time.hour << ":" << dt.time.minute << ":" << dt.time.second << endl;
    return 0;
}