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
            cout << "Библиотека пуста.\n";
            return;
        }
        cout << "\nСписок всех книг в библиотеке:\n";
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
        cout << "1. Добавить книгу\n";
        cout << "2. Удалить книгу по названию\n";
        cout << "3. Найти книги по автору\n";
        cout << "4. Показать все книги\n";
        cout << "5. Выйти\n";
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
                    cout << "Книга удалена.\n";
                } else {
                    cout << "Книга не найдена.\n";
                }
                break;
            }
            
            case 3: {
                string author;
                cout << "Введите автора для поиска: ";
                getline(cin, author);
                vector<Book> found = library.searchByAuthor(author);
                if (found.empty()) {
                    cout << "Книги автора \"" << author << "\" не найдены.\n";
                } else {
                    cout << "Найдено книг: " << found.size() << "\n";
                    for (const auto& book : found) {
                        cout << "- " << book.title 
                             << " (Год: " << book.year 
                             << ", Жанр: " << book.genre << ")\n";
                    }
                }
                break;
            }
            
            case 4:
                library.displayAll();
                break;
                
            case 5:
                cout << "Выход из программы.\n";
                break;
                
            default:
                cout << "Неверный выбор.\n";
                break;
        }  
    } while (choice != 5);
    return 0;
}