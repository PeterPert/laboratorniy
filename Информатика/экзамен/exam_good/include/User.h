#ifndef USER_H
#define USER_H

#include <memory>
#include <vector>
#include <string>
#include "Order.h"

class User {
protected:
    int userId;
    std::string name;
    std::string email;
    std::string role;
    std::vector<std::shared_ptr<Order>> orders;

public:
    User(int id, const std::string& name, const std::string& email, const std::string& role);
    virtual ~User() = default;
    
    // Чисто виртуальные функции
    virtual void displayMenu() = 0;
    virtual bool hasPermission(const std::string& action) const = 0;
    
    // Общие методы
    virtual std::shared_ptr<Order> createOrder();
    virtual std::string viewOrderStatus(int orderId);
    virtual bool cancelOrder(int orderId);
    
    // Геттеры
    int getUserId() const { return userId; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    std::string getRole() const { return role; }
    
    // Управление заказами
    void addOrder(std::shared_ptr<Order> order);
    std::vector<std::shared_ptr<Order>> getOrders() const;
};

#endif // USER_H