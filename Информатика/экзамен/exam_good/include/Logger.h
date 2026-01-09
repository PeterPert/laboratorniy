#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <memory>
#include "DatabaseConnection.h"

class Logger {
private:
    std::shared_ptr<DatabaseConnection<std::string>> db;
    
public:
    Logger(std::shared_ptr<DatabaseConnection<std::string>> database);
    
    void logAction(int userId, const std::string& entityType, 
                   int entityId, const std::string& operation, 
                   const std::string& details = "");
    
    std::vector<std::vector<std::string>> getAuditLogByUser(int userId);
};

#endif // LOGGER_H