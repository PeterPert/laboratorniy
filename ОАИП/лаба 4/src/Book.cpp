#include "library_manager/Book.h"
#include "library_manager/Logger.h"
#include <pqxx/pqxx>
#include <vector>


Book::Book(const std::string& t, int a_id, int pub_year, const std::string& g)
    : title(t), author_id(a_id), publication_year(pub_year), genre(g) {}

    
void Book::save(pqxx::connection& conn) {
    try {
        pqxx::work txn(conn);

        if (id == -1) {
            pqxx::result res = txn.exec(
                "INSERT INTO books (title, author_id, publication_year, genre) VALUES (" + txn.quote(title) + ", " + 
                txn.quote(author_id) + ", " + txn.quote(publication_year) + ", " +
                txn.quote(genre) + ") RETURNING id"
            );
            id = res[0]["id"].as<int>();
            Logger::info("Book added: " + title + " (ID: " + std::to_string(id) + ")");
        } else {
            txn.exec(
                "UPDATE books SET title = " + txn.quote(title) + 
                ", author_id = " + txn.quote(author_id) + 
                ", publication_year = " + txn.quote(publication_year) + 
                ", genre = " + txn.quote(genre) + 
                " WHERE id = " + txn.quote(id)
            );
            Logger::info("Book updated: " + title + " (ID: " + std::to_string(id) + ")");
        }
        txn.commit();
    } catch (const std::exception& e) {
        Logger::error("Error saving book: " + std::string(e.what()));
        throw;
    }
}


std::string Book::getDescription() const {
    return title + " (" + std::to_string(publication_year) + ") - " + genre;
}


std::vector<Book> Book::findByTitle(pqxx::connection& conn, const std::string& title) {
    std::vector<Book> books;

    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT * FROM books WHERE title ILIKE " + txn.quote("%" + title + "%")
        );
        
        for (const auto& row : res) {
            Book book(
                row["title"].c_str(),
                row["author_id"].as<int>(),
                row["publication_year"].as<int>(),
                row["genre"].c_str()
            );
            book.id = row["id"].as<int>();
            books.push_back(book);
        }
        Logger::info("Found " + std::to_string(books.size()) + " books with title: " + title);
    } catch (const std::exception& e) {
        Logger::error("Error finding books by title: " + std::string(e.what()));
        throw;
    }
    return books;
}


std::vector<Book> Book::findByAuthor(pqxx::connection& conn, int author_id) {
    std::vector<Book> books;

    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT * FROM books WHERE author_id = " + txn.quote(author_id)
        );
        
        for (const auto& row : res) {
            Book book(
                row["title"].c_str(),
                row["author_id"].as<int>(),
                row["publication_year"].as<int>(),
                row["genre"].c_str()
            );
            book.id = row["id"].as<int>();
            books.push_back(book);
        }
        Logger::info("Found " + std::to_string(books.size()) + " books by author ID: " + std::to_string(author_id));
    } catch (const std::exception& e) {
        Logger::error("Error finding books by author: " + std::string(e.what()));
        throw;
    }
    return books;
}


Book Book::findById(pqxx::connection& conn, int book_id) {
    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT * FROM books WHERE id = " + txn.quote(book_id)
        );
        
        Book book(
            res[0]["title"].c_str(),
            res[0]["author_id"].as<int>(),
            res[0]["publication_year"].as<int>(),
            res[0]["genre"].c_str()
        );
        book.id = res[0]["id"].as<int>();

        return book;
    } catch (const std::exception& e) {
        Logger::error("Error finding book by ID: " + std::string(e.what()));
        throw;
    }
}

int Book::getAuthorId() const {return author_id;}
int Book::getPublicationYear() const {return publication_year;}
int Book::getId() const {return id;}
std::string Book::getTitle() const {return title;}
std::string Book::getGenre() const {return genre;}

void Book::setTitle(const std::string& new_title) {title = new_title;}
void Book::setAuthorId(int new_author_id) {author_id = new_author_id;}
void Book::setPublicationYear(int new_publication_year) {publication_year = new_publication_year;}
void Book::setGenre(const std::string& new_genre) {genre = new_genre;}


FictionBook::FictionBook(const std::string& t, int a_id, int pub_year)
    : Book(t, a_id, pub_year, "Fiction") {}

std::string FictionBook::getDescription() const {
    return getTitle() + " (" + std::to_string(getPublicationYear()) + ") - Fiction";
}


NonFictionBook::NonFictionBook(const std::string& t, int a_id, int pub_year)
    : Book(t, a_id, pub_year, "Non-Fiction") {}

std::string NonFictionBook::getDescription() const {
    return getTitle() + " (" + std::to_string(getPublicationYear()) + ") - Non-Fiction";
}