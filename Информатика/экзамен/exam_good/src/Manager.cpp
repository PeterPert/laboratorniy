
#include "../include/Manager.h"
#include "../include/DatabaseConnection.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>

// Явная специализация для устранения проблемы с шаблоном
template class DatabaseConnection<std::string>;

Manager::Manager(int id, const std::string& name, const std::string& email,
                 std::shared_ptr<DatabaseConnection<std::string>> database)
    : User(id, name, email, "manager"), db(database) {}

void Manager::displayMenu() {
    std::cout << "\n=== Меню менеджера ===\n";
    std::cout << "1. Просмотр заказов в ожидании утверждения\n";
    std::cout << "2. Утвердить заказ\n";
    std::cout << "3. Обновить количество товара на складе\n";
    std::cout << "4. Просмотр деталей заказа\n";
    std::cout << "5. Изменить статус заказа\n";
    std::cout << "6. Просмотр истории утверждённых заказов\n";
    std::cout << "7. Просмотр истории статусов заказов\n";
    std::cout << "8. Выход\n";
    std::cout << "Выберите действие: ";
}

bool Manager::hasPermission(const std::string& action) const {
    static const std::vector<std::string> allowedActions = {
        "view_orders", "approve_order", "update_stock",
        "view_order_details", "update_order_status"
    };
    
    return std::find(allowedActions.begin(), allowedActions.end(), action) 
           != allowedActions.end();
}

bool Manager::updateStock(int productId, int newQuantity) {
    std::cout << "\n=== Обновление количества товара ===\n";
    
    try {
        // Проверяем существует ли товар
        auto productCheck = db->executeQuery(
            "SELECT name, stock_quantity FROM products WHERE product_id = " + 
            std::to_string(productId)
        );
        
        if (productCheck.empty()) {
            std::cout << "Товар с ID " << productId << " не найден" << std::endl;
            return false;
        }
        
        std::string productName = productCheck[0][0];
        int currentStock = std::stoi(productCheck[0][1]);
        
        std::cout << "Товар: " << productName << " (ID: " << productId << ")\n";
        std::cout << "Текущее количество: " << currentStock << "\n";
        std::cout << "Новое количество: " << newQuantity << "\n\n";
        
        // Проверяем корректность
        if (newQuantity < 0) {
            std::cout << "Ошибка: количество не может быть отрицательным" << std::endl;
            return false;
        }
        
        std::cout << "Вы уверены, что хотите изменить количество? (y/n): ";
        char confirm;
        std::cin >> confirm;
        
        if (confirm != 'y' && confirm != 'Y') {
            std::cout << "Отменено пользователем" << std::endl;
            return false;
        }
        
        // Выполняем обновление
        std::string query = 
            "UPDATE products SET stock_quantity = " + std::to_string(newQuantity) + 
            " WHERE product_id = " + std::to_string(productId);
        
        db->executeNonQuery(query);
        
        std::cout << "✓ Количество товара обновлено\n";
        std::cout << "Было: " << currentStock << ", стало: " << newQuantity << std::endl;
        
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка обновления количества товара: " << e.what() << std::endl;
        return false;
    }
}

void Manager::viewPendingOrders() {
    try {
        auto result = db->executeQuery(
            "SELECT o.order_id, u.name, o.total_price, o.order_date "
            "FROM orders o JOIN users u ON o.user_id = u.user_id "
            "WHERE o.status = 'pending' "
            "ORDER BY o.order_date"
        );
        
        std::cout << "\n=== Заказы в ожидании утверждения ===\n";
        if (result.empty()) {
            std::cout << "Нет заказов в ожидании" << std::endl;
            return;
        }
        
        std::cout << std::left << std::setw(10) << "ID" 
                  << std::setw(20) << "Пользователь" 
                  << std::setw(15) << "Сумма" 
                  << std::setw(20) << "Дата" << std::endl;
        std::cout << std::string(65, '-') << std::endl;
        
        for (const auto& row : result) {
            std::cout << std::left << std::setw(10) << row[0]
                      << std::setw(20) << row[1]
                      << std::setw(15) << row[2]
                      << std::setw(20) << row[3] << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

bool Manager::approveOrder(int orderId) {
    try {
        std::string query = "UPDATE orders SET status = 'completed' WHERE order_id = " + 
                           std::to_string(orderId);
        db->executeNonQuery(query);
        std::cout << "✓ Заказ утвержден" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return false;
    }
}

void Manager::viewOrderDetails(int orderId) {
    try {
        auto orderInfo = db->executeQuery(
            "SELECT o.order_id, u.name, o.status, o.total_price, o.order_date "
            "FROM orders o JOIN users u ON o.user_id = u.user_id "
            "WHERE o.order_id = " + std::to_string(orderId)
        );
        
        if (orderInfo.empty()) {
            std::cout << "Заказ не найден" << std::endl;
            return;
        }
        
        std::cout << "\n=== Детали заказа #" << orderId << " ===\n";
        std::cout << "Покупатель: " << orderInfo[0][1] << std::endl;
        std::cout << "Статус: " << orderInfo[0][2] << std::endl;
        std::cout << "Сумма: " << orderInfo[0][3] << " руб." << std::endl;
        std::cout << "Дата: " << orderInfo[0][4] << "\n" << std::endl;
        
        // Товары в заказе
        auto items = db->executeQuery(
            "SELECT p.name, oi.quantity, oi.price, (oi.quantity * oi.price) as total "
            "FROM order_items oi "
            "JOIN products p ON oi.product_id = p.product_id "
            "WHERE oi.order_id = " + std::to_string(orderId)
        );
        
        if (!items.empty()) {
            std::cout << "Товары в заказе:\n";
            std::cout << std::left << std::setw(20) << "Товар" 
                      << std::setw(10) << "Кол-во" 
                      << std::setw(10) << "Цена" 
                      << std::setw(10) << "Сумма" << std::endl;
            std::cout << std::string(50, '-') << std::endl;
            
            double orderTotal = 0;
            for (const auto& row : items) {
                std::cout << std::left << std::setw(20) << row[0]
                          << std::setw(10) << row[1]
                          << std::setw(10) << row[2]
                          << std::setw(10) << row[3] << std::endl;
                orderTotal += std::stod(row[3]);
            }
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Итого: " << orderTotal << " руб." << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

bool Manager::updateOrderStatus(int orderId, const std::string& newStatus) {
    try {
        std::string query = "UPDATE orders SET status = '" + newStatus + 
                           "' WHERE order_id = " + std::to_string(orderId);
        db->executeNonQuery(query);
        std::cout << "✓ Статус заказа " << orderId 
                  << " изменен на: " << newStatus << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return false;
    }
}

void Manager::viewApprovedOrdersHistory() {
    try {
        auto result = db->executeQuery(
            "SELECT o.order_id, u.name, o.total_price, o.order_date "
            "FROM orders o JOIN users u ON o.user_id = u.user_id "
            "WHERE o.status = 'completed' "
            "ORDER BY o.order_date DESC"
        );
        
        std::cout << "\n=== История утверждённых заказов ===\n";
        if (result.empty()) {
            std::cout << "Нет утвержденных заказов" << std::endl;
            return;
        }
        
        std::cout << std::left << std::setw(10) << "ID" 
                  << std::setw(20) << "Пользователь" 
                  << std::setw(15) << "Сумма" 
                  << std::setw(20) << "Дата" << std::endl;
        std::cout << std::string(65, '-') << std::endl;
        
        for (const auto& row : result) {
            std::cout << std::left << std::setw(10) << row[0]
                      << std::setw(20) << row[1]
                      << std::setw(15) << row[2]
                      << std::setw(20) << row[3] << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void Manager::viewOrderStatusHistory(int orderId) {
    try {
        auto result = db->executeQuery(
            "SELECT old_status, new_status, changed_at, "
            "(SELECT name FROM users WHERE user_id = osh.changed_by) "
            "FROM order_status_history osh "
            "WHERE order_id = " + std::to_string(orderId) + 
            " ORDER BY changed_at DESC"
        );
        
        if (result.empty()) {
            std::cout << "История статусов заказа " << orderId << " не найдена" << std::endl;
            return;
        }
        
        std::cout << "\n=== История статусов заказа #" << orderId << " ===\n";
        std::cout << std::left << std::setw(15) << "Было" 
                  << std::setw(15) << "Стало" 
                  << std::setw(25) << "Дата изменения" 
                  << std::setw(20) << "Кто изменил" << std::endl;
        std::cout << std::string(75, '-') << std::endl;
        
        for (const auto& row : result) {
            std::string oldStatus = row[0].empty() ? "—" : row[0];
            std::cout << std::left << std::setw(15) << oldStatus
                      << std::setw(15) << row[1]
                      << std::setw(25) << row[2]
                      << std::setw(20) << row[3] << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}