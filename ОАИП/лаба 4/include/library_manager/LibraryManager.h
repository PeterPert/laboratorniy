#pragma once


#include "Database.h"
#include "Author.h"
#include "Book.h"
#include "User.h"
#include "BorrowedBook.h"
#include "Pair.h"
#include <memory>
#include <vector>


class LibraryManager {
    private:
        Database db;
    
    public:
        LibraryManager(const std::string& conn_str);

        void clearDatabase();
        void addAuthor(const std::string& name, int birth_year);
        void addBook(const std::string& title, int author_id, int publication_year, 
                const std::string& genre, bool is_fiction = true);
        void addUser(const std::string& name);
        void borrowBook(int user_id, int book_id);
        void returnBook(int user_id, int book_id);
    
        std::vector<Author> findAuthorsByName(const std::string& name);
        std::vector<Book> findBooksByTitle(const std::string& title);
        std::vector<User> findUsersByName(const std::string& name);
        std::vector<Book> findBooksByAuthor(int author_id);
    
        void listBooksByAuthor(int author_id);
        void getUsersRegisteredLastYear();
        void getBooksBorrowedLast30Days();
        void getTop3PopularBooks();
        void getAuthorsWithBookCount();
    
        bool isBookAvailable(int book_id);
        Database& getDatabase();
};