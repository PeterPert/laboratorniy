#include "../include/User.h"
#include <iostream>
#include <algorithm>

User::User(int id, const std::string& name, const std::string& email, const std::string& role)
    : userId(id), name(name), email(email), role(role) {}

std::shared_ptr<Order> User::createOrder() {
    auto order = std::make_shared<Order>(orders.size() + 1, userId);
    orders.push_back(order);
    return order;
}

std::string User::viewOrderStatus(int orderId) {
    auto it = std::find_if(orders.begin(), orders.end(),
        [orderId](const std::shared_ptr<Order>& order) {
            return order->getOrderId() == orderId;
        });
    
    if (it != orders.end()) {
        return (*it)->getStatus();
    }
    return "Заказ не найден";
}

bool User::cancelOrder(int orderId) {
    auto it = std::find_if(orders.begin(), orders.end(),
        [orderId](const std::shared_ptr<Order>& order) {
            return order->getOrderId() == orderId;
        });
    
    if (it != orders.end() && (*it)->getStatus() == "pending") {
        (*it)->setStatus("canceled");
        return true;
    }
    return false;
}

void User::addOrder(std::shared_ptr<Order> order) {
    orders.push_back(order);
}

std::vector<std::shared_ptr<Order>> User::getOrders() const {
    return orders;
}