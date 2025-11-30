#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Student { 
    int id; 
    char name[50]; 
    int age; 
    double average_grade;
};

int main() {
    Student students[] = { 
        {1, "Иван Петров", 20, 4.5}, 
        {2, "Мария Сидорова", 19, 4.8}, 
        {3, "Алексей Иванов", 21, 4.2} 
    };
    
    // Запись
    ofstream out("students.dat", ios::binary);
    int count = 3;
    for (int i = 0; i < count; i++) {
        out.write(reinterpret_cast<char*>(&students[i]), sizeof(Student));
    }
    out.close();
    
    // Чтение
    ifstream in("students.dat", ios::binary);
    
    // Подсчет количества студентов
    in.seekg(0, ios::end);
    int size = in.tellg();
    in.seekg(0, ios::beg);
    int total = size / sizeof(Student);
    
    cout << "Всего студентов: " << total << endl;
    cout << "Список студентов:" << endl;
    
    Student s;
    Student best;
    double max_grade = 0;
    
    for (int i = 0; i < total; i++) {
        in.read(reinterpret_cast<char*>(&s), sizeof(Student));
        cout << s.id << ". " << s.name << ", " << s.age << " лет, балл: " << s.average_grade << endl;
        
        if (s.average_grade > max_grade) {
            max_grade = s.average_grade;
            best = s;
        }
    }
    in.close();
    cout << "Лучший студент: " << best.name << " с баллом " << best.average_grade << endl;
    return 0;
}