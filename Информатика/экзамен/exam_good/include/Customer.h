
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "PaymentStrategy.h"
#include <memory>
#include <vector>

// Предварительное объявление
template<typename T>
class DatabaseConnection;

class Customer : public User {
private:
    int loyaltyLevel;
    std::shared_ptr<DatabaseConnection<std::string>> db;
    
public:
    Customer(int id, const std::string& name, const std::string& email, 
             int loyaltyLevel, std::shared_ptr<DatabaseConnection<std::string>> database);
    
    void displayMenu() override;
    bool hasPermission(const std::string& action) const override;
    
    // Методы для работы с заказами (теперь с БД)
    std::shared_ptr<Order> createOrder();
    void addToOrder(int orderId, int productId, int quantity);
    bool removeFromOrder(int orderId, int orderItemId);
    bool makePayment(int orderId, std::unique_ptr<PaymentStrategy> paymentStrategy);
    void viewMyOrders();
    bool returnOrder(int orderId);
    void viewOrderStatusHistory(int orderId);
    
    // Новые методы для работы с БД
    bool addProductToOrderDB(int orderId, int productId, int quantity);
    bool removeProductFromOrderDB(int orderId, int productId);
    std::vector<std::vector<std::string>> getMyOrdersFromDB();
    std::string getOrderStatusFromDB(int orderId);
    bool processReturnDB(int orderId);
    
    int getLoyaltyLevel() const { return loyaltyLevel; }
};

#endif // CUSTOMER_H