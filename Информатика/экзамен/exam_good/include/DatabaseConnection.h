#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <memory>
#include <string>
#include <vector>
#include <pqxx/pqxx>

template<typename T>
class DatabaseConnection {
private:
    std::unique_ptr<pqxx::connection> conn;
    std::unique_ptr<pqxx::work> transaction;
    std::string connectionString;

public:
    // Конструктор
    explicit DatabaseConnection(const std::string& connStr);
    
    // Деструктор
    ~DatabaseConnection();
    
    // Выполнение запроса с возвратом данных
    std::vector<std::vector<std::string>> executeQuery(const std::string& query);
    
    // Выполнение запроса без возврата данных
    void executeNonQuery(const std::string& query);
    
    // Управление транзакциями
    void beginTransaction();
    void commitTransaction();
    void rollbackTransaction();
    
    // Создание функций и триггеров
    void createFunction(const std::string& functionSql);
    void createTrigger(const std::string& triggerSql);
    
    // Проверка состояния транзакции
    bool isTransactionActive() const;
    
    // Получение соединения
    pqxx::connection* getConnection() const;
};

#endif // DATABASECONNECTION_H