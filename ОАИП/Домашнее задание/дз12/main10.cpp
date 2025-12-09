#include <iostream>
#include <string>
using namespace std;
class Publication {
public:
    string title; 

    // Конструктор
    Publication(string t) {
        title = t;
    }
};

// Производный класс
class Book : public Publication {
public:
    string author;  
    int year;      
    
    // Конструктор с параметрами
    Book(string t, string a, int y) : Publication(t) {
        author = a;
        year = y;
    }
    
    void displayInfo() {
        cout << "Название: " << title 
             << ", Автор: " << author 
             << ", Год выпуска: " << year << endl;
    }
};

int main() {
    Book book("Преступление и наказание", "Федор Достоевский", 1866);
    book.displayInfo();
    return 0;
}