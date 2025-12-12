#include "library_manager/User.h"
#include "library_manager/Logger.h"
#include <pqxx/pqxx>
#include <vector>


User::User(const std::string& n) : name(n) {}


void User::save(pqxx::connection& conn) {
    try {
        pqxx::work txn(conn);

        if (id == -1) {
            pqxx::result res = txn.exec(
                "INSERT INTO users (name) VALUES (" + txn.quote(name) + ") RETURNING id, registration_date"
            );

            id = res[0]["id"].as<int>();
            registration_date = res[0]["registration_date"].c_str();

            Logger::info("User added: " + name + " (ID: " + std::to_string(id) + ")");
        } else {
            txn.exec(
                "UPDATE users SET name = " + txn.quote(name) + 
                " WHERE id = " + txn.quote(id)
            );
            Logger::info("User updated: " + name + " (ID: " + std::to_string(id) + ")");
        }
        txn.commit();
    } catch (const std::exception& e) {
        Logger::error("Error saving user: " + std::string(e.what()));
        throw;
    }
}


std::vector<User> User::findByName(pqxx::connection& conn, const std::string& name) {
    std::vector<User> users;

    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT * FROM users WHERE name ILIKE " + txn.quote("%" + name + "%")
        );
        
        for (const auto& row : res) {
            User user(row["name"].c_str());
            user.id = row["id"].as<int>();
            user.registration_date = row["registration_date"].c_str();
            
            users.push_back(user);
        }

        Logger::info("Found " + std::to_string(users.size()) + " users with name: " + name);
    } catch (const std::exception& e) {
        Logger::error("Error finding user: " + std::string(e.what()));
        throw;
    }

    return users;
}


User User::findById(pqxx::connection& conn, int user_id) {
    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT * FROM users WHERE id = " + txn.quote(user_id)
        );
        
        if (res.empty()) {
            throw std::runtime_error("User not found with ID: " + std::to_string(user_id));
        }
        
        User user(res[0]["name"].c_str());
        user.id = res[0]["id"].as<int>();
        user.registration_date = res[0]["registration_date"].c_str();

        return user;
    } catch (const std::exception& e) {
        Logger::error("Error finding user by ID: " + std::string(e.what()));
        throw;
    }
}


int User::getCountRegisteredLastYear(pqxx::connection& conn) {
    try {
        pqxx::work txn(conn);

        pqxx::result res = txn.exec(
            "SELECT COUNT(*) as count FROM users WHERE "
            "registration_date >= CURRENT_DATE - INTERVAL '1 year'"
        );
        
        int count = res[0]["count"].as<int>();

        Logger::info("Users registered in the last year: " + std::to_string(count));
        return count;
    } catch (const std::exception& e) {
        Logger::error("Error getting users count: " + std::string(e.what()));
        throw;
    }
}


int User::getId() const {return id;}
std::string User::getName() const {return name;}
std::string User::getRegistrationDate() const {return registration_date;}

void User::setName(const std::string& new_name) {name = new_name;}