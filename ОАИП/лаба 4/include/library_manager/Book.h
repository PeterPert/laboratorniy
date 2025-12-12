#pragma once


#include <string>
#include <vector>


namespace pqxx {
    class connection;
}


class Book {
    protected:
        int id = -1;
        std::string title;
        int author_id;
        int publication_year;
        std::string genre;
    
    public:
        Book(const std::string& t, int a_id, int pub_year, const std::string& g);
        virtual ~Book() = default;
        
        virtual void save(pqxx::connection& conn);
        virtual std::string getDescription() const;
        
        static std::vector<Book> findByAuthor(pqxx::connection& conn, int author_id);
        static std::vector<Book> findByTitle(pqxx::connection& conn, const std::string& title);
        static Book findById(pqxx::connection& conn, int book_id);
        
        int getId() const;
        std::string getTitle() const;
        int getAuthorId() const;
        int getPublicationYear() const;
        std::string getGenre() const;
        
        void setTitle(const std::string& new_title);
        void setAuthorId(int new_author_id);
        void setPublicationYear(int new_publication_year);
        void setGenre(const std::string& new_genre);
};

class FictionBook : public Book {
    public:
        FictionBook(const std::string& t, int a_id, int pub_year);
        std::string getDescription() const override;
};

class NonFictionBook : public Book {
    public:
        NonFictionBook(const std::string& t, int a_id, int pub_year);
        std::string getDescription() const override;
};