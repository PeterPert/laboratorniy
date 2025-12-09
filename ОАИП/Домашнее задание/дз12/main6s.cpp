#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Book {
    string title;
    string author;
    int year;
    string genre;
};

struct Library {
    vector<Book> books; 
    
    void addBook(const Book& book) {
        books.push_back(book);
    }
    
    bool removeBook(const string& title) {
        for (auto it = books.begin(); it != books.end(); ) {
            if (it->title == title) { // у нас здесь не указатели, а итераторы, которые используются для разыменования кэша из вектора
                it = books.erase(it);  
                return true;
            } else {
                ++it;  
            }
        }
        return false;
    }
    
    vector<Book> searchByAuthor(const string& author) {
        vector<Book> result;
        for (const auto& book : books) {
            if (book.author == author) {
                result.push_back(book);
            }
        }
        return result;
    }
    
    void displayAll() {
        if (books.empty()) {
            cout << "Библиотека пуста." << endl;
            return;
        }
        cout << "Список всех книг в библиотеке:" << endl;
        for (int i = 0; i < books.size(); i++) {
            cout << i + 1 << ". " << books[i].title 
                 << " (Автор: " << books[i].author 
                 << ", Год: " << books[i].year 
                 << ", Жанр: " << books[i].genre << ")\n";
        }
        cout << "Всего книг: " << books.size() << "\n";
    }
};

int main() {
    Library library;
    int choice;
    do {
        cout << "\n=== Меню ===\n";
        cout << "1. Добавить книгу" << endl;
        cout << "2. Удалить книгу по названию" << endl;
        cout << "3. Найти книги по автору" << endl;
        cout << "4. Показать все книги" << endl;
        cout << "5. Выйти" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                Book book;
                cout << "Введите название: ";
                getline(cin, book.title);
                cout << "Введите автора: ";
                getline(cin, book.author);
                cout << "Введите год издания: ";
                cin >> book.year;
                cin.ignore();
                cout << "Введите жанр: ";
                getline(cin, book.genre);
                library.addBook(book);
                cout << "Книга добавлена." << endl;
                break;
            }
            
            case 2: {
                string title;
                cout << "Введите название книги для удаления: ";
                getline(cin, title);
                if (library.removeBook(title)) {
                    cout << "Книга удалена." << endl;
                } else {
                    cout << "Книга не найдена." << endl;
                }
                break;
            }
            
            case 3: {
                string author;
                cout << "Введите автора для поиска: ";
                getline(cin, author);
                vector<Book> found = library.searchByAuthor(author);
                if (found.empty()) {
                    cout << "Книги автора \"" << author << "\" не найдены." << endl;
                } else {
                    cout << "Найдено книг: " << found.size() << endl;
                    for (const auto& book : found) {
                        cout << "- " << book.title 
                             << " (Год: " << book.year 
                             << ", Жанр: " << book.genre << ")" << endl;
                    }
                }
                break;
            }
            
            case 4:
                library.displayAll();
                break;
                
            case 5:
                cout << "Выход из программы." << endl;
                break;
                
            default:
                cout << "Неверный выбор." << endl;
                break;
        }  
    } while (choice != 5);
    return 0;
}