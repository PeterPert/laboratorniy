#include "../include/DatabaseConnection.h"
#include <stdexcept>
#include <iostream>

// Явная специализация шаблона для std::string
template class DatabaseConnection<std::string>;

template<typename T>
DatabaseConnection<T>::DatabaseConnection(const std::string& connStr) 
    : connectionString(connStr) {
    try {
        conn = std::make_unique<pqxx::connection>(connectionString);
        if (!conn->is_open()) {
            throw std::runtime_error("Не удалось подключиться к базе данных");
        }
        std::cout << "Подключение к базе данных установлено успешно" << std::endl;
    } catch (const std::exception& e) {
        throw std::runtime_error("Ошибка подключения к БД: " + std::string(e.what()));
    }
}

template<typename T>
DatabaseConnection<T>::~DatabaseConnection() {
    try {
        if (transaction) {
            transaction->abort();
        }
        if (conn && conn->is_open()) {
            conn->close();
        }
    } catch (...) {
        // Игнорируем ошибки при деструкторе
    }
}

template<typename T>
std::vector<std::vector<std::string>> DatabaseConnection<T>::executeQuery(const std::string& query) {
    try {
        pqxx::nontransaction ntx(*conn);
        pqxx::result result = ntx.exec(query);
        
        std::vector<std::vector<std::string>> rows;
        for (const auto& row : result) {
            std::vector<std::string> cols;
            for (const auto& field : row) {
                cols.push_back(field.c_str());
            }
            rows.push_back(cols);
        }
        return rows;
    } catch (const std::exception& e) {
        throw std::runtime_error("Ошибка выполнения запроса: " + std::string(e.what()));
    }
}

template<typename T>
void DatabaseConnection<T>::executeNonQuery(const std::string& query) {
    try {
        if (transaction) {
            transaction->exec(query);
        } else {
            pqxx::work work(*conn);
            work.exec(query);
            work.commit();
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Ошибка выполнения команды: " + std::string(e.what()));
    }
}

template<typename T>
void DatabaseConnection<T>::beginTransaction() {
    try {
        transaction = std::make_unique<pqxx::work>(*conn);
    } catch (const std::exception& e) {
        throw std::runtime_error("Ошибка начала транзакции: " + std::string(e.what()));
    }
}

template<typename T>
void DatabaseConnection<T>::commitTransaction() {
    try {
        if (transaction) {
            transaction->commit();
            transaction.reset();
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Ошибка коммита транзакции: " + std::string(e.what()));
    }
}

template<typename T>
void DatabaseConnection<T>::rollbackTransaction() {
    try {
        if (transaction) {
            transaction->abort();
            transaction.reset();
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Ошибка отката транзакции: " + std::string(e.what()));
    }
}

template<typename T>
void DatabaseConnection<T>::createFunction(const std::string& functionSql) {
    executeNonQuery(functionSql);
}

template<typename T>
void DatabaseConnection<T>::createTrigger(const std::string& triggerSql) {
    executeNonQuery(triggerSql);
}

template<typename T>
bool DatabaseConnection<T>::isTransactionActive() const {
    return transaction != nullptr;
}

template<typename T>
pqxx::connection* DatabaseConnection<T>::getConnection() const {
    return conn.get();
}