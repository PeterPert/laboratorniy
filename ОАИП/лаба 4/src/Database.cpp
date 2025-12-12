#include "library_manager/Database.h"
#include "library_manager/Logger.h"


Database::Database(const std::string& conn_str) : connection_string(conn_str) {}


void Database::initializeDatabase() {
    try {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);
        
        txn.exec(
            "CREATE TABLE IF NOT EXISTS authors ("
            "id SERIAL PRIMARY KEY, "
            "name VARCHAR(100) NOT NULL, "
            "birth_year INTEGER"
            ")"
        );
        
        txn.exec(
            "CREATE TABLE IF NOT EXISTS books ("
            "id SERIAL PRIMARY KEY, "
            "title VARCHAR(100) NOT NULL, "
            "author_id INTEGER REFERENCES authors(id), "
            "publication_year INTEGER, "
            "genre VARCHAR(50)"
            ")"
        );
        
        txn.exec(
            "CREATE TABLE IF NOT EXISTS users ("
            "id SERIAL PRIMARY KEY, "
            "name VARCHAR(100) NOT NULL, "
            "registration_date DATE DEFAULT CURRENT_DATE"
            ")"
        );
        
        txn.exec(
            "CREATE TABLE IF NOT EXISTS borrowed_books ("
            "user_id INTEGER REFERENCES users(id), "
            "book_id INTEGER REFERENCES books(id), "
            "borrow_date DATE DEFAULT CURRENT_DATE, "
            "return_date DATE, "
            "PRIMARY KEY (user_id, book_id)"
            ")"
        );
        
        txn.exec("CREATE INDEX IF NOT EXISTS idx_authors_name ON authors(name)");
        txn.exec("CREATE INDEX IF NOT EXISTS idx_books_title ON books(title)");
        txn.exec("CREATE INDEX IF NOT EXISTS idx_borrowed_books_date ON borrowed_books(borrow_date)");
        
        txn.commit();
        Logger::log("Database initialized successfully");
    } catch (const std::exception& e) {
        Logger::log("Error initializing database: " + std::string(e.what()));
        throw;
    }
}


void Database::clearDatabase(){
    try {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);

        txn.exec("SET session_replication_role = 'replica'");

        txn.exec("DELETE FROM borrowed_books");
        txn.exec("DELETE FROM books");
        txn.exec("DELETE FROM users");
        txn.exec("DELETE FROM authors");

        txn.exec("ALTER SEQUENCE authors_id_seq RESTART WITH 1");
        txn.exec("ALTER SEQUENCE books_id_seq RESTART WITH 1");
        txn.exec("ALTER SEQUENCE users_id_seq RESTART WITH 1");

        txn.exec("SET session_replication_role = 'origin'");

        txn.commit();
        Logger::info("Database cleared successfully");
    } catch (const std::exception& e){
        Logger::error("Error clearing database: " + std::string(e.what()));
        throw;
    }
}


pqxx::connection Database::getConnection() {
    return pqxx::connection(connection_string);
}