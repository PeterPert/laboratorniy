#include "library_manager/LibraryManager.h"
#include "library_manager/Logger.h"
#include <iostream>


LibraryManager::LibraryManager(const std::string& conn_str) : db(conn_str) {
    db.initializeDatabase();
}


void LibraryManager::addAuthor(const std::string& name, int birth_year) {
    auto conn = db.getConnection();
    
    Author author(name, birth_year);
    author.save(conn);
}


void LibraryManager::returnBook(int user_id, int book_id) {
    auto conn = db.getConnection();

    BorrowedBook borrowed_book(user_id, book_id);
    borrowed_book.returnBook(conn);
}


void LibraryManager::clearDatabase(){
    db.clearDatabase();
}


void LibraryManager::addBook(const std::string& title, int author_id, int publication_year, 
                            const std::string& genre, bool is_fiction) {
    auto conn = db.getConnection();
    
    std::unique_ptr<Book> book;
    if (is_fiction) {
        book = std::make_unique<FictionBook>(title, author_id, publication_year);
    } else {
        book = std::make_unique<NonFictionBook>(title, author_id, publication_year);
    }
    book -> save(conn);
}


void LibraryManager::borrowBook(int user_id, int book_id) {
    auto conn = db.getConnection();

    BorrowedBook borrowed_book(user_id, book_id);
    borrowed_book.borrow(conn);
}


std::vector<User> LibraryManager::findUsersByName(const std::string& name) {
    auto conn = db.getConnection();

    return User::findByName(conn, name);
}


std::vector<Book> LibraryManager::findBooksByAuthor(int author_id) {
    auto conn = db.getConnection();

    return Book::findByAuthor(conn, author_id);
}


Database& LibraryManager::getDatabase() {
    return db;
}


void LibraryManager::listBooksByAuthor(int author_id) {
    auto books = findBooksByAuthor(author_id);
    
    std::cout << "Books by author ID " << author_id << ":\n";
    for (const auto& book : books) {
        std::cout << "- " << book.getTitle() << " (" << book.getPublicationYear() 
                  << ") - " << book.getGenre() << std::endl;
    }
    Logger::info("Listed books by author: " + std::to_string(author_id));
}


void LibraryManager::getUsersRegisteredLastYear() {
    auto conn = db.getConnection();
    
    int count = User::getCountRegisteredLastYear(conn);
    std::cout << "Users registered in the last year: " << count << std::endl;
}


void LibraryManager::addUser(const std::string& name) {
    auto conn = db.getConnection();

    User user(name);
    user.save(conn);
}


void LibraryManager::getBooksBorrowedLast30Days() {
    auto conn = db.getConnection();
    auto records = BorrowedBook::getBooksBorrowedLast30Days(conn);
    
    std::cout << "Books borrowed in last 30 days:\n";
    for (const auto& record : records) {
        std::cout << "- " << record.book_title << " by " << record.author_name 
                  << " borrowed by " << record.user_name 
                  << " on " << record.borrow_date;
        if (record.return_date != "Not returned") {
            std::cout << " (returned: " << record.return_date << ")";
        }
        std::cout << std::endl;
    }
}


void LibraryManager::getAuthorsWithBookCount() {
    auto conn = db.getConnection();
    try {
        pqxx::work txn(conn);
        pqxx::result res = txn.exec(
            "SELECT a.name, COUNT(b.id) as book_count "
            "FROM authors a "
            "LEFT JOIN books b ON a.id = b.author_id "
            "GROUP BY a.id, a.name "
            "ORDER BY book_count DESC"
        );
        
        std::vector<Pair<std::string, int>> authorBookPairs;
        for (const auto& row : res) {
            authorBookPairs.emplace_back(
                row["name"].c_str(), 
                row["book_count"].as<int>()
            );
        }
        
        std::cout << "Authors and their book counts:\n";
        for (const auto& pair : authorBookPairs) {
            std::cout << "- " << pair.getFirst() << ": " 
                     << pair.getSecond() << " books" << std::endl;
        }
        Logger::info("Listed authors with book counts");
    } catch (const std::exception& e) {
        Logger::error("Error getting authors with book counts: " + std::string(e.what()));
        throw;
    }
}


bool LibraryManager::isBookAvailable(int book_id) {
    auto conn = db.getConnection();
    return !BorrowedBook::isBookBorrowed(conn, book_id);
}


std::vector<Author> LibraryManager::findAuthorsByName(const std::string& name) {
    auto conn = db.getConnection();
    return Author::findByName(conn, name);
}


std::vector<Book> LibraryManager::findBooksByTitle(const std::string& title) {
    auto conn = db.getConnection();
    return Book::findByTitle(conn, title);
}


void LibraryManager::getTop3PopularBooks() {
    auto conn = db.getConnection();
    auto records = BorrowedBook::getTopPopularBooks(conn, 3);
    
    std::cout << "Top 3 most popular books:\n";
    int rank = 1;
    for (const auto& record : records) {
        std::cout << rank << ". " << record.book_title << " by " 
                  << record.author_name << std::endl;
        rank++;
    }
}