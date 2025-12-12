#pragma once


#include <string>
#include <vector>


namespace pqxx {class connection;}


class Author {
    private:
        int id = -1;
        std::string name;
        int birth_year;
        
    public:
        Author(const std::string& n, int b_year);
        
        void save(pqxx::connection& conn);
        static std::vector<Author> findByName(pqxx::connection& conn, const std::string& name);
        static Author findById(pqxx::connection& conn, int author_id);
        
        int getId() const;
        std::string getName() const;
        int getBirthYear() const;
        
        void setName(const std::string& new_name);
        void setBirthYear(int new_birth_year);
};