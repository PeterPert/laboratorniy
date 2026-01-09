#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <string>

class OrderItem {
private:
    int orderItemId;
    int orderId;
    int productId;
    int quantity;
    double price;
    std::string productName;

public:
    OrderItem(int id, int orderId, int productId, int quantity, 
              double price, const std::string& productName);
    ~OrderItem() = default;
    
    // Геттеры
    int getOrderItemId() const { return orderItemId; }
    int getOrderId() const { return orderId; }
    int getProductId() const { return productId; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    std::string getProductName() const { return productName; }
    
    // Сеттеры
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }
    
    // Расчет стоимости позиции
    double calculateSubtotal() const { return price * quantity; }
};

#endif // ORDERITEM_H