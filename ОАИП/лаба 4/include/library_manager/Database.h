#pragma once


#include <string>
#include <pqxx/pqxx>


class Logger;


class Database {
    private:
        std::string connection_string;
    
    public:
        Database(const std::string& conn_str);
    
        void initializeDatabase();
        void clearDatabase();
        
        pqxx::connection getConnection();
};