#include "../include/Utils.h"
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>

std::vector<std::shared_ptr<Order>> Utils::filterOrdersByStatus(
    const std::vector<std::shared_ptr<Order>>& orders, 
    const std::string& status) {
    
    std::vector<std::shared_ptr<Order>> filteredOrders;
    
    std::copy_if(orders.begin(), orders.end(), 
                 std::back_inserter(filteredOrders),
                 [&status](const std::shared_ptr<Order>& order) {
                     return order->getStatus() == status;
                 });
    
    return filteredOrders;
}

double Utils::calculateTotalAmount(const std::vector<std::shared_ptr<Order>>& orders) {
    return std::accumulate(orders.begin(), orders.end(), 0.0,
        [](double total, const std::shared_ptr<Order>& order) {
            return total + order->getTotalPrice();
        });
}

int Utils::countOrdersByStatus(const std::vector<std::shared_ptr<Order>>& orders, 
                              const std::string& status) {
    return std::count_if(orders.begin(), orders.end(),
        [&status](const std::shared_ptr<Order>& order) {
            return order->getStatus() == status;
        });
}

bool Utils::checkPermission(const std::string& userRole, 
                           const std::string& requiredPermission) {
    // Простая логика проверки прав
    if (userRole == "admin") return true;
    if (userRole == "manager") {
        return requiredPermission == "view_orders" || 
               requiredPermission == "approve_order" ||
               requiredPermission == "update_stock";
    }
    if (userRole == "customer") {
        return requiredPermission == "view_own_orders" ||
               requiredPermission == "make_payment";
    }
    return false;
}

bool Utils::generateCSVReport(const std::string& filename, 
                             const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
    
    file.close();
    return true;
}