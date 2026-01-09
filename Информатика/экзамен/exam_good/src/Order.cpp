#include "../include/Order.h"
#include <algorithm>
#include <iostream>

Order::Order(int id, int userId) 
    : orderId(id), userId(userId), status("pending"), 
      totalPrice(0.0), orderDate("2024-01-01") {}

void Order::addItem(std::unique_ptr<OrderItem> item) {
    items.push_back(std::move(item));
    calculateTotal();
}

bool Order::removeItem(int productId) {
    auto it = std::find_if(items.begin(), items.end(),
        [productId](const std::unique_ptr<OrderItem>& item) {
            return item->getProductId() == productId;
        });
    
    if (it != items.end()) {
        items.erase(it);
        calculateTotal();
        return true;
    }
    return false;
}

void Order::calculateTotal() {
    totalPrice = 0.0;
    for (const auto& item : items) {
        totalPrice += item->getPrice() * item->getQuantity();
    }
}

bool Order::canReturn() const {
    // Проверка: статус completed и не прошло 30 дней
    return status == "completed";
}