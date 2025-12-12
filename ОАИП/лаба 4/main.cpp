#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "library_manager/LibraryManager.h"


void AddAuthor(LibraryManager& library) {
    std::string name;
    short birth_year = 0;
    
    std::cin.ignore();
    std::cout << "Enter author name: ";
    std::getline(std::cin, name);

    std::cout << "Enter birth year: ";
    std::cin >> birth_year;
    
    try {
        library.addAuthor(name, birth_year);
        std::cout << "Author added successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error adding author: " << e.what() << "\n";
    }
}


std::string low(const std::string& line){
    std::string res = line;

    for (size_t i = 0; i < res.size(); i++){
        res[i] = std::tolower(res[i]);
    }

    return res;
}


void AddBook(LibraryManager& library) {
    std::string title, genre, line;
    int author_id = 0, publication_year = 0;
    char book_type = ' ';
    
    std::cin.ignore();
    std::cout << "Enter book title: ";
    std::getline(std::cin, title);

    std::cout << "Enter author ID: ";
    std::cin >> author_id;

    std::cout << "Enter publication year: ";
    std::cin >> publication_year;
    
    std::cin.ignore();
    std::cout << "Enter type of book(fict || non-fict): ";
    std::getline(std::cin, line);

    bool is_fiction = false;

    if (low(line) == "fiction"){
        genre = "Fiction";
        is_fiction = true;
    } else {
        std::cout << "Enter genre of book: ";
        std::getline(std::cin, genre);
    }
    
    try {
        library.addBook(title, author_id, publication_year, genre, is_fiction);
        std::cout << "Book added successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error adding book: " << e.what() << "\n";
    }
}


void ShowOperations() {
    std::cout << "\n=== Library Management System ===\n";
    
    std::cout << "Add Author: 1\n";
    std::cout << "Add Book: 2\n";
    std::cout << "Add User: 3\n";
    std::cout << "Borrow Book: 4\n";
    std::cout << "Return Book: 5\n";
    std::cout << "Find Authors by Name: 6\n";
    std::cout << "Find Books by Title: 7\n";
    std::cout << "Find Users by Name: 8\n";
    std::cout << "List Books by Author: 9\n";
    std::cout << "Users Registered Last Year: 10\n";
    std::cout << "Books Borrowed Last 30 Days: 11\n";
    std::cout << "Top 3 Popular Books: 12\n";
    std::cout << "Authors with Book Counts: 13\n";
    std::cout << "Check Book Availability: 14\n";
    std::cout << "Delete inf from database: 15\n";
    std::cout << "Exit: 0\n";
    
    std::cout << "Enter choice: ";
}


void BorrowBook(LibraryManager& library) {
    int user_id = 0, book_id = 0;
    
    std::cout << "Enter user ID: ";
    std::cin >> user_id;

    std::cout << "Enter book ID: ";
    std::cin >> book_id;
    
    try {
        if (library.isBookAvailable(book_id)) {
            library.borrowBook(user_id, book_id);
            std::cout << "Book borrowed successfully!\n";
        } else {
            std::cout << "Book is currently not available for borrowing.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error borrowing book: " << e.what() << "\n";
    }
}


void CheckBookAvailability(LibraryManager& library) {
    int book_id = 0;
    
    std::cout << "Enter book ID to check: ";
    std::cin >> book_id;
    
    try {
        if (library.isBookAvailable(book_id)) {
            std::cout << "Book is available for borrowing.\n";
        } else {
            std::cout << "Book is currently borrowed.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error checking book availability: " << e.what() << "\n";
    }
}


void ReturnBook(LibraryManager& library) {
    int user_id = 0, book_id = 0;
    
    std::cout << "Enter user ID: ";
    std::cin >> user_id;

    std::cout << "Enter book ID: ";
    std::cin >> book_id;
    
    try {
        library.returnBook(user_id, book_id);
        std::cout << "Book returned!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error returning book: " << e.what() << "\n";
    }
}


void FindAuthors(LibraryManager& library) {
    std::string name;
    
    std::cin.ignore();
    std::cout << "Enter author name to search: ";
    std::getline(std::cin, name);
    
    try {
        auto authors = library.findAuthorsByName(name);
        
        if (authors.empty()) {
            std::cout << "No authors found with name: " << name << "\n";
        } else {
            std::cout << "Found authors:\n";
            
            for (const auto& author : authors) {
                std::cout << "- ID: " << author.getId() << ", Name: " << author.getName() 
                         << ", Birth Year: " << author.getBirthYear() << "\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error finding authors: " << e.what() << "\n";
    }
}


void FindBooks(LibraryManager& library) {
    std::string title;
    
    std::cin.ignore();
    std::cout << "Enter book title to search: ";
    std::getline(std::cin, title);
    
    try {
        auto books = library.findBooksByTitle(title);
        
        if (books.empty()) {
            std::cout << "No books found with title: " << title << "\n";
        } else {
            std::cout << "Found books:\n";
            for (const auto& book : books) {
                std::cout << "- ID: " << book.getId() << ", Title: " << book.getTitle() 
                         << ", Author ID: " << book.getAuthorId() 
                         << ", Year: " << book.getPublicationYear() 
                         << ", Genre: " << book.getGenre() << "\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error finding books: " << e.what() << "\n";
    }
}


void FindUsers(LibraryManager& library) {
    std::string name;
    
    std::cout << "Enter user name to search: ";
    std::getline(std::cin, name);
    
    try {
        auto users = library.findUsersByName(name);
        
        if (users.empty()) {
            std::cout << "No users found with name: " << name << "\n";
        } else {
            std::cout << "Found users:\n";
            for (const auto& user : users) {
                std::cout << "- ID: " << user.getId() << ", Name: " << user.getName() 
                         << ", Registered: " << user.getRegistrationDate() << "\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error finding users: " << e.what() << "\n";
    }
}


auto getPassword(){
    std::ifstream file("bin/config.txt");
    std::string line;

    if (file.fail()){
        std::cout << "Error with read password from file" << "\n";
        return line;
    }

    file >> line;

    file.close();
    return line;
}


void AddUser(LibraryManager& library) {
    std::string name;
    
    std::cout << "Enter user name: ";
    std::getline(std::cin, name);
    
    try {
        library.addUser(name);
        std::cout << "User added successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error adding user: " << e.what() << "\n";
    }
}


void ClearDatabase(LibraryManager& library){
    std::cout << "P.S. This actions will delete all data from database\n";

    std::string line;

    std::cout << "Enter confirm(yes || no): ";
    std::getline(std::cin, line);

    if (line == "yes"){
        try {
            library.clearDatabase();
            std::cout << "Database cleared!\n";
        } catch (const std::exception& e){
            std::cerr << "Error of clearing: " << e.what() << "\n"; 
        }
    } else std::cout << "Database won't be deleted\n";
}


int main() {
    std::string password = getPassword();

    try {
        std::string conn_str = "dbname=library user=postgres password= " + password + " host=localhost port=5432";
        LibraryManager library(conn_str);
        
        std::cout << "Library Management System Started Successfully!\n";
        std::cout << "Connected to database: \n";
        
        short n = 0;
        do {
            ShowOperations();
            std::cin >> n;
            std::cin.ignore();
            
            switch (n) {
                case 1:
                    AddAuthor(library);
                    break;
                case 2:
                    AddBook(library);
                    break;
                case 3:
                    AddUser(library);
                    break;
                case 4:
                    BorrowBook(library);
                    break;
                case 5:
                    ReturnBook(library);
                    break;
                case 6:
                    FindAuthors(library);
                    break;
                case 7:
                    FindBooks(library);
                    break;
                case 8:
                    FindUsers(library);
                    break;
                case 9: {
                    int author_id;
                    std::cout << "Enter author ID: ";
                    std::cin >> author_id;
                    std::cin.ignore();
                    library.listBooksByAuthor(author_id);
                    break;
                }
                case 10:
                    library.getUsersRegisteredLastYear();
                    break;
                case 11:
                    library.getBooksBorrowedLast30Days();
                    break;
                case 12:
                    library.getTop3PopularBooks();
                    break;
                case 13:
                    library.getAuthorsWithBookCount();
                    break;
                case 14:
                    CheckBookAvailability(library);
                    break;
                case 15:
                    ClearDatabase(library);
                    break;
                case 0:
                    std::cout << "The end!\n";
                    break;
                default:
                    std::cout << "Invalid option!\n";
            }
            
            if (n != 0) {
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
            }
            
        } while (n != 0);
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << "\n";
        std::cerr << "Please check your database connection settings and ensure PostgreSQL is running." << "\n";
        return 1;
    }
    
    return 0;
}