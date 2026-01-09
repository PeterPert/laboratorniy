
#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"
#include <memory>
#include <string>

// Предварительное объявление
template<typename T>
class DatabaseConnection;

class Manager : public User {
private:
    std::shared_ptr<DatabaseConnection<std::string>> db;
    
public:
    Manager(int id, const std::string& name, const std::string& email,
            std::shared_ptr<DatabaseConnection<std::string>> database);
    
    void displayMenu() override;
    bool hasPermission(const std::string& action) const override;
    
    // Специфичные методы менеджера
    void viewPendingOrders();
    bool approveOrder(int orderId);
    bool updateStock(int productId, int newQuantity);  // Новый метод
    void viewOrderDetails(int orderId);
    bool updateOrderStatus(int orderId, const std::string& newStatus);
    void viewApprovedOrdersHistory();
    void viewOrderStatusHistory(int orderId);
    
    // Методы для работы с БД
    bool updateProductStockDB(int productId, int newQuantity);
    std::vector<std::vector<std::string>> getProductInfo(int productId);
};

#endif // MANAGER_H