#include "library_manager/Author.h"
#include "library_manager/Logger.h"
#include <pqxx/pqxx>
#include <vector>


Author::Author(const std::string& n, int b_year) : name(n), birth_year(b_year) {}


void Author::save(pqxx::connection& conn) {
    try {
        pqxx::work txn(conn);

        if (id == -1) {
            pqxx::result res = txn.exec(
                "INSERT INTO authors (name, birth_year) VALUES (" +
                txn.quote(name) + ", " + txn.quote(birth_year) + ") RETURNING id"
            );
            id = res[0]["id"].as<int>();
            Logger::info("Author added: " + name + " (ID: " + std::to_string(id) + ")");
        } else {
            txn.exec(
                "UPDATE authors SET name = " + txn.quote(name) + 
                ", birth_year = " + txn.quote(birth_year) + 
                " WHERE id = " + txn.quote(id)
            );
            Logger::info("Author updated: " + name + " (ID: " + std::to_string(id) + ")");
        }
        txn.commit();
    } catch (const std::exception& e) {
        Logger::error("Error saving author: " + std::string(e.what()));
        throw;
    }
}


Author Author::findById(pqxx::connection& conn, int author_id) {
    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT * FROM authors WHERE id = " + txn.quote(author_id)
        );
        
        
        Author author(res[0]["name"].c_str(), res[0]["birth_year"].as<int>());
        author.id = res[0]["id"].as<int>();

        return author;
    } catch (const std::exception& e) {
        Logger::error("Error finding author by ID: " + std::string(e.what()));
        throw;
    }
}


std::vector<Author> Author::findByName(pqxx::connection& conn, const std::string& name) {
    std::vector<Author> authors;

    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT * FROM authors WHERE name ILIKE " + txn.quote("%" + name + "%")
        );
        
        for (const auto& row : res) {
            Author author(row["name"].c_str(), row["birth_year"].as<int>());
            author.id = row["id"].as<int>();
            authors.push_back(author);
        }
        Logger::info("Found " + std::to_string(authors.size()) + " authors with name: " + name);
    } catch (const std::exception& e) {
        Logger::error("Error finding author: " + std::string(e.what()));
        throw;
    }
    
    return authors;
}


int Author::getId() const {return id;}
std::string Author::getName() const {return name;}
int Author::getBirthYear() const {return birth_year;}

void Author::setName(const std::string& new_name) {name = new_name;}
void Author::setBirthYear(int new_birth_year) {birth_year = new_birth_year;}