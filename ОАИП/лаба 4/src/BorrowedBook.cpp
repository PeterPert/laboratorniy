#include "library_manager/BorrowedBook.h"
#include "library_manager/Logger.h"
#include <pqxx/pqxx>
#include <vector>


BorrowedBook::BorrowedBook(int u_id, int b_id) : user_id(u_id), book_id(b_id) {}


void BorrowedBook::borrow(pqxx::connection& conn) {
    try {
        if (isBookBorrowed(conn, book_id)) {
            throw std::runtime_error("Book is already borrowed");
        }
        
        pqxx::work txn(conn);
        
        txn.exec(
            "INSERT INTO borrowed_books (user_id, book_id) VALUES (" +
            txn.quote(user_id) + ", " + txn.quote(book_id) + ")"
        );
        txn.commit();
        
        Logger::info("Book borrowed - User ID: " + std::to_string(user_id) + 
                    ", Book ID: " + std::to_string(book_id));
    } catch (const std::exception& e) {
        Logger::error("Error borrowing book: " + std::string(e.what()));
        throw;
    }
}


std::vector<BorrowRecord> BorrowedBook::getBooksBorrowedLast30Days(pqxx::connection& conn) {
    std::vector<BorrowRecord> records;
    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT bb.user_id, bb.book_id, bb.borrow_date, bb.return_date, "
            "b.title as book_title, u.name as user_name, a.name as author_name "
            "FROM borrowed_books bb "
            "JOIN books b ON bb.book_id = b.id "
            "JOIN authors a ON b.author_id = a.id "
            "JOIN users u ON bb.user_id = u.id "
            "WHERE bb.borrow_date >= CURRENT_DATE - INTERVAL '30 days' "
            "ORDER BY bb.borrow_date DESC"
        );
        
        for (const auto& row : res) {
            BorrowRecord record;
            record.user_id = row["user_id"].as<int>();
            record.book_id = row["book_id"].as<int>();
            record.borrow_date = row["borrow_date"].c_str();
            record.return_date = row["return_date"].is_null() ? "Not returned" : row["return_date"].c_str();
            record.book_title = row["book_title"].c_str();
            record.user_name = row["user_name"].c_str();
            record.author_name = row["author_name"].c_str();
            records.push_back(record);
        }
        Logger::info("Found " + std::to_string(records.size()) + " books borrowed in last 30 days");
    } catch (const std::exception& e) {
        Logger::error("Error getting borrowed books: " + std::string(e.what()));
        throw;
    }
    return records;
}


bool BorrowedBook::hasUserBorrowedBook(pqxx::connection& conn, int user_id, int book_id) {
    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT 1 FROM borrowed_books WHERE user_id = " + 
            txn.quote(user_id) + " AND book_id = " + txn.quote(book_id) +
            " AND return_date IS NULL"
        );
        return !res.empty();
    } catch (const std::exception& e) {
        Logger::error("Error checking user book borrowing: " + std::string(e.what()));
        throw;
    }
}


std::vector<BorrowRecord> BorrowedBook::getTopPopularBooks(pqxx::connection& conn, int limit) {
    std::vector<BorrowRecord> records;

    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT b.id as book_id, b.title as book_title, a.name as author_name, "
            "COUNT(bb.book_id) as borrow_count "
            "FROM books b "
            "JOIN authors a ON b.author_id = a.id "
            "JOIN borrowed_books bb ON b.id = bb.book_id "
            "GROUP BY b.id, b.title, a.name "
            "ORDER BY borrow_count DESC "
            "LIMIT " + std::to_string(limit)
        );
        
        for (const auto& row : res) {
            BorrowRecord record;
            record.book_id = row["book_id"].as<int>();
            record.book_title = row["book_title"].c_str();
            record.author_name = row["author_name"].c_str();
            records.push_back(record);
        }
        Logger::info("Found top " + std::to_string(records.size()) + " popular books");
    } catch (const std::exception& e) {
        Logger::error("Error getting popular books: " + std::string(e.what()));
        throw;
    }
    return records;
}

bool BorrowedBook::isBookBorrowed(pqxx::connection& conn, int book_id) {
    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT 1 FROM borrowed_books WHERE book_id = " + 
            txn.quote(book_id) + " AND return_date IS NULL"
        );
        return !res.empty();
    } catch (const std::exception& e) {
        Logger::error("Error checking if book is borrowed: " + std::string(e.what()));
        throw;
    }
}


void BorrowedBook::returnBook(pqxx::connection& conn) {
    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "UPDATE borrowed_books SET return_date = CURRENT_DATE WHERE " +
            std::string("user_id = ") + txn.quote(user_id) + 
            " AND book_id = " + txn.quote(book_id) +
            " AND return_date IS NULL RETURNING borrow_date"
        );
        
        if (res.affected_rows() == 0) {
            throw std::runtime_error("No active borrowing record found");
        }
        
        txn.commit();
        Logger::info("Book returned - User ID: " + std::to_string(user_id) + 
                    ", Book ID: " + std::to_string(book_id));
    } catch (const std::exception& e) {
        Logger::error("Error returning book: " + std::string(e.what()));
        throw;
    }
}

int BorrowedBook::getUserId() const {return user_id;}
int BorrowedBook::getBookId() const {return book_id;}

std::string BorrowedBook::getBorrowDate() const {return borrow_date;}
std::string BorrowedBook::getReturnDate() const {return return_date;}