#pragma once


#include <string>
#include <vector>


namespace pqxx {
    class connection;
}


struct BorrowRecord {
    int user_id;
    int book_id;
    std::string borrow_date;
    std::string return_date;
    std::string book_title;
    std::string user_name;
    std::string author_name;
};

class BorrowedBook {
    private:
        int user_id;
        int book_id;
        std::string borrow_date;
        std::string return_date;
    
    public:
        BorrowedBook(int u_id, int b_id);
        
        void borrow(pqxx::connection& conn);
        void returnBook(pqxx::connection& conn);
        
        static std::vector<BorrowRecord> getBooksBorrowedLast30Days(pqxx::connection& conn);
        static std::vector<BorrowRecord> getTopPopularBooks(pqxx::connection& conn, int limit = 3);
        static bool isBookBorrowed(pqxx::connection& conn, int book_id);
        static bool hasUserBorrowedBook(pqxx::connection& conn, int user_id, int book_id);
        
        int getUserId() const;
        int getBookId() const;
        std::string getBorrowDate() const;
        std::string getReturnDate() const;
};