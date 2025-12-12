#pragma once


#include <string>
#include <vector>


namespace pqxx {
    class connection;
}


class User {
    private:
        int id = -1;
        std::string name;
        std::string registration_date;
        
    public:
        User(const std::string& n);
        
        void save(pqxx::connection& conn);
        static std::vector<User> findByName(pqxx::connection& conn, const std::string& name);
        static User findById(pqxx::connection& conn, int user_id);
        
        static int getCountRegisteredLastYear(pqxx::connection& conn);
        
        int getId() const;
        std::string getName() const;
        std::string getRegistrationDate() const;
        
        void setName(const std::string& new_name);
};