#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int productId;
    std::string name;
    double price;
    int stockQuantity;
    std::string description;

public:
    Product(int id, const std::string& name, double price, 
            int stockQuantity, const std::string& description = "");
    ~Product() = default;
    
    // Геттеры
    int getProductId() const { return productId; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }
    std::string getDescription() const { return description; }
    
    // Сеттеры
    void setPrice(double newPrice) { price = newPrice; }
    void setStockQuantity(int newQuantity) { stockQuantity = newQuantity; }
    void setName(const std::string& newName) { name = newName; }
    
    // Проверка наличия на складе
    bool isAvailable(int requestedQuantity) const {
        return stockQuantity >= requestedQuantity;
    }
    
    // Уменьшение количества на складе
    bool reduceStock(int quantity) {
        if (stockQuantity >= quantity) {
            stockQuantity -= quantity;
            return true;
        }
        return false;
    }
    
    // Увеличение количества на складе
    void increaseStock(int quantity) {
        stockQuantity += quantity;
    }
};

#endif // PRODUCT_H