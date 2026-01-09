#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Product.h"
#include <memory>

class Admin : public User {
public:
    Admin(int id, const std::string& name, const std::string& email);
    
    void displayMenu() override;
    bool hasPermission(const std::string& action) const override;
    
    // Специфичные методы администратора
    void addProduct(std::unique_ptr<Product> product);
    bool updateProduct(int productId, const std::string& field, const std::string& value);
    bool deleteProduct(int productId);
    void viewAllOrders();
    bool updateOrderStatus(int orderId, const std::string& newStatus);
    void viewOrderHistory(int orderId);
    void viewAuditLog();
    void generateReport(const std::string& filename);
};

#endif // ADMIN_H