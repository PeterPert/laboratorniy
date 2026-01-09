#ifndef ORDER_H
#define ORDER_H

#include <memory>
#include <vector>
#include <string>
#include "OrderItem.h"
#include "Payment.h"

class Order {
private:
    int orderId;
    int userId;
    std::string status;
    double totalPrice;
    std::string orderDate;
    std::vector<std::unique_ptr<OrderItem>> items;
    std::unique_ptr<Payment> payment;

public:
    Order(int id, int userId);
    ~Order() = default;
    
    // Добавление и удаление товаров
    void addItem(std::unique_ptr<OrderItem> item);
    bool removeItem(int productId);
    
    // Расчет общей суммы
    void calculateTotal();
    
    // Геттеры и сеттеры
    int getOrderId() const { return orderId; }
    int getUserId() const { return userId; }
    std::string getStatus() const { return status; }
    void setStatus(const std::string& newStatus) { status = newStatus; }
    double getTotalPrice() const { return totalPrice; }
    std::string getOrderDate() const { return orderDate; }
    
    const std::vector<std::unique_ptr<OrderItem>>& getItems() const { return items; }
    
    // Проверка возможности возврата
    bool canReturn() const;
};

#endif // ORDER_H