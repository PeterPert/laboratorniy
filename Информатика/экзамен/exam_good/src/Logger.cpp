#include "../include/Logger.h"
#include <iostream>

Logger::Logger(std::shared_ptr<DatabaseConnection<std::string>> database) 
    : db(database) {}

void Logger::logAction(int userId, const std::string& entityType, 
                       int entityId, const std::string& operation, 
                       const std::string& details) {
    // ВАЖНО: Не включаем log_id в список столбцов
    std::string query = 
        "INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, performed_at) "
        "VALUES ('" + entityType + "', " + std::to_string(entityId) + 
        ", '" + operation + "', " + std::to_string(userId) + ", CURRENT_TIMESTAMP)";
    
    try {
        db->executeNonQuery(query);
        std::cout << "✓ Действие залогировано: " << operation << " " << entityType 
                  << " #" << entityId << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка логирования: " << e.what() << std::endl;
        
        // Дополнительная отладочная информация
        std::cerr << "SQL запрос: " << query << std::endl;
    }
}

std::vector<std::vector<std::string>> Logger::getAuditLogByUser(int userId) {
    std::string query = 
        "SELECT log_id, entity_type, entity_id, operation, performed_at "
        "FROM audit_log WHERE performed_by = " + 
        std::to_string(userId) + " ORDER BY performed_at DESC";
    
    try {
        return db->executeQuery(query);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка получения логов: " << e.what() << std::endl;
        return {};
    }
}