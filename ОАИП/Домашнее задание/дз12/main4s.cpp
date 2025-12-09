#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Employee {
    string name;
    int age;
    string position;
    double salary;
};

int main() {
    int n;
    cout << "Введите количество сотрудников: ";
    cin >> n;
    cin.ignore();
    vector<Employee> employees(n);//нужен n чтобы добавляла уже в существующий элемент Employee в списке
    for (int i = 0; i < n; i++) {
        cout << " Сотрудник " << i + 1 << endl;
        cout << "Введите имя: ";
        getline(cin, employees[i].name);
        
        cout << "Введите возраст: ";
        cin >> employees[i].age;
        cin.ignore();
        
        cout << "Введите должность: ";
        getline(cin, employees[i].position);
        
        cout << "Введите зарплату: ";
        cin >> employees[i].salary;
        cin.ignore();
    }
    if (employees.empty()) {
        cout << "Нет данных о сотрудниках!" << endl;
        return 0;
    }
    int youngIndex = 0;
    int oldIndex = 0;
    double totalSalary = employees[0].salary;
    
    for (int i = 1; i < n; i++) {
        totalSalary += employees[i].salary;
        
        if (employees[i].age < employees[youngIndex].age) {
            youngIndex = i;
        }
        
        if (employees[i].age > employees[oldIndex].age) {
            oldIndex = i;
        }
    }
    cout << "Самый молодой сотрудник: " 
         << employees[youngIndex].name 
         << ", возраст: " << employees[youngIndex].age
         << ", должность: " << employees[youngIndex].position
         << ", зарплата: " << employees[youngIndex].salary << endl;
    
    cout << "Самый старший сотрудник: " 
         << employees[oldIndex].name 
         << ", возраст: " << employees[oldIndex].age
         << ", должность: " << employees[oldIndex].position
         << ", зарплата: " << employees[oldIndex].salary << endl;
    
    double averageSalary = totalSalary / n;
    cout << "Средняя зарплата всех сотрудников: " << averageSalary << endl;
    return 0;
}