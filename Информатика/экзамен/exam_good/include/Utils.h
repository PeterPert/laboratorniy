#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <memory>
#include <string>
#include "Order.h"

namespace Utils {
    // Фильтрация заказов по статусу
    std::vector<std::shared_ptr<Order>> filterOrdersByStatus(
        const std::vector<std::shared_ptr<Order>>& orders, 
        const std::string& status);
    
    // Подсчет общей суммы заказов
    double calculateTotalAmount(const std::vector<std::shared_ptr<Order>>& orders);
    
    // Подсчет количества заказов по статусу
    int countOrdersByStatus(const std::vector<std::shared_ptr<Order>>& orders, 
                           const std::string& status);
    
    // Проверка прав доступа
    bool checkPermission(const std::string& userRole, 
                        const std::string& requiredPermission);
    
    // Генерация CSV отчета
    bool generateCSVReport(const std::string& filename, 
                          const std::vector<std::vector<std::string>>& data);
}

#endif // UTILS_H