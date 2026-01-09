// #include "../include/Customer.h"
// #include <iostream>
// #include <algorithm>  
// #include <string>     

// Customer::Customer(int id, const std::string& name, const std::string& email, int loyaltyLevel)
//     : User(id, name, email, "customer"), loyaltyLevel(loyaltyLevel) {}

// void Customer::displayMenu() {
//     std::cout << "\n=== Меню покупателя ===\n";
//     std::cout << "1. Создать новый заказ\n";
//     std::cout << "2. Добавить товар в заказ\n";
//     std::cout << "3. Удалить товар из заказа\n";
//     std::cout << "4. Просмотр моих заказов\n";
//     std::cout << "5. Просмотр статуса заказа\n";
//     std::cout << "6. Оплатить заказ\n";
//     std::cout << "7. Оформить возврат заказа\n";
//     std::cout << "8. Просмотр истории статусов заказа\n";
//     std::cout << "9. Выход\n";
//     std::cout << "Выберите действие: ";
// }

// bool Customer::hasPermission(const std::string& action) const {
//     static const std::vector<std::string> allowedActions = {
//         "create_order", "view_orders", "pay_order",
//         "return_order", "view_history"
//     };
    
//     return std::find(allowedActions.begin(), allowedActions.end(), action) 
//            != allowedActions.end();
// }

// void Customer::addToOrder(int orderId, int productId, int quantity) {
//     std::cout << "Товар " << productId << " добавлен в заказ " 
//               << orderId << " в количестве " << quantity << std::endl;
// }

// bool Customer::removeFromOrder(int orderId, int orderItemId) {
//     std::cout << "Товар " << orderItemId << " удален из заказа " 
//               << orderId << std::endl;
//     return true;
// }

// bool Customer::makePayment(int orderId, std::unique_ptr<PaymentStrategy> paymentStrategy) {
//     std::cout << "Оплата заказа " << orderId << "..." << std::endl;
//     if (paymentStrategy) {
//         paymentStrategy->pay(100.0); // Пример суммы
//         return true;
//     }
//     return false;
// }

// void Customer::viewMyOrders() {
//     std::cout << "Мои заказы:" << std::endl;
//     for (const auto& order : orders) {
//         std::cout << "Заказ #" << order->getOrderId() 
//                   << " - Статус: " << order->getStatus() << std::endl;
//     }
// }

// void Customer::returnOrder(int orderId) {
//     std::cout << "Оформление возврата заказа " << orderId << std::endl;
// }

// void Customer::viewOrderStatusHistory(int orderId) {
//     std::cout << "История статусов заказа " << orderId << ":" << std::endl;
// }
#include "../include/Customer.h"
#include "../include/DatabaseConnection.h"
#include "../include/Payment.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

Customer::Customer(int id, const std::string& name, const std::string& email, 
                   int loyaltyLevel, std::shared_ptr<DatabaseConnection<std::string>> database)
    : User(id, name, email, "customer"), loyaltyLevel(loyaltyLevel), db(database) {}

void Customer::displayMenu() {
    std::cout << "\n=== Меню покупателя ===\n";
    std::cout << "1. Создать новый заказ\n";
    std::cout << "2. Добавить товар в заказ\n";
    std::cout << "3. Удалить товар из заказа\n";
    std::cout << "4. Просмотр моих заказов\n";
    std::cout << "5. Просмотр статуса заказа\n";
    std::cout << "6. Оплатить заказ\n";
    std::cout << "7. Оформить возврат заказа\n";
    std::cout << "8. Просмотр истории статусов заказа\n";
    std::cout << "9. Выход\n";
    std::cout << "Выберите действие: ";
}

bool Customer::hasPermission(const std::string& action) const {
    static const std::vector<std::string> allowedActions = {
        "create_order", "view_orders", "pay_order",
        "return_order", "view_history"
    };
    
    return std::find(allowedActions.begin(), allowedActions.end(), action) 
           != allowedActions.end();
}

std::shared_ptr<Order> Customer::createOrder() {
    try {
        auto result = db->executeQuery("SELECT COALESCE(MAX(order_id), 0) + 1 FROM orders");
        int nextOrderId = result.empty() ? 1 : std::stoi(result[0][0]);
        
        std::string query = 
            "INSERT INTO orders (order_id, user_id, status, total_price, order_date) "
            "VALUES (" + std::to_string(nextOrderId) + ", " + 
            std::to_string(getUserId()) + ", 'pending', 0.00, CURRENT_TIMESTAMP)";
        
        db->executeNonQuery(query);
        
        auto order = std::make_shared<Order>(nextOrderId, getUserId());
        addOrder(order);
        
        std::cout << "✓ Создан новый заказ #" << nextOrderId << std::endl;
        return order;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка создания заказа: " << e.what() << std::endl;
        return nullptr;
    }
}

bool Customer::addProductToOrderDB(int orderId, int productId, int quantity) {
    try {
        // Проверка заказа
        auto orderCheck = db->executeQuery(
            "SELECT user_id FROM orders WHERE order_id = " + std::to_string(orderId)
        );
        
        if (orderCheck.empty()) {
            std::cout << "Заказ #" << orderId << " не найден" << std::endl;
            return false;
        }
        
        if (std::stoi(orderCheck[0][0]) != getUserId()) {
            std::cout << "Это не ваш заказ!" << std::endl;
            return false;
        }
        
        // Проверка товара
        auto productCheck = db->executeQuery(
            "SELECT name, price, stock_quantity FROM products WHERE product_id = " + 
            std::to_string(productId)
        );
        
        if (productCheck.empty()) {
            std::cout << "Товар #" << productId << " не найден" << std::endl;
            return false;
        }
        
        int stock = std::stoi(productCheck[0][2]);
        if (stock < quantity) {
            std::cout << "Недостаточно товара на складе. Доступно: " << stock << std::endl;
            return false;
        }
        
        // Добавление товара
        std::string query = 
            "INSERT INTO order_items (order_id, product_id, quantity, price) "
            "VALUES (" + std::to_string(orderId) + ", " + std::to_string(productId) + 
            ", " + std::to_string(quantity) + ", " + productCheck[0][1] + ")";
        
        db->executeNonQuery(query);
        
        // Обновление суммы
        db->executeNonQuery(
            "UPDATE orders SET total_price = ("
            "SELECT SUM(quantity * price) FROM order_items WHERE order_id = " + 
            std::to_string(orderId) + ") WHERE order_id = " + std::to_string(orderId)
        );
        
        // Уменьшение склада
        db->executeNonQuery(
            "UPDATE products SET stock_quantity = stock_quantity - " + 
            std::to_string(quantity) + " WHERE product_id = " + std::to_string(productId)
        );
        
        std::cout << "✓ Товар \"" << productCheck[0][0] << "\" добавлен в заказ #" 
                  << orderId << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка добавления товара: " << e.what() << std::endl;
        return false;
    }
}

void Customer::addToOrder(int orderId, int productId, int quantity) {
    std::cout << "Товар " << productId << " добавлен в заказ " 
              << orderId << " в количестве " << quantity << std::endl;
}

bool Customer::removeProductFromOrderDB(int orderId, int productId) {
    try {
        // Проверка заказа
        auto orderCheck = db->executeQuery(
            "SELECT user_id FROM orders WHERE order_id = " + std::to_string(orderId)
        );
        
        if (orderCheck.empty()) {
            std::cout << "Заказ #" << orderId << " не найден" << std::endl;
            return false;
        }
        
        if (std::stoi(orderCheck[0][0]) != getUserId()) {
            std::cout << "Это не ваш заказ!" << std::endl;
            return false;
        }
        
        // Проверка наличия товара в заказе
        auto itemCheck = db->executeQuery(
            "SELECT quantity FROM order_items WHERE order_id = " + 
            std::to_string(orderId) + " AND product_id = " + std::to_string(productId)
        );
        
        if (itemCheck.empty()) {
            std::cout << "Товар #" << productId << " не найден в заказе #" << orderId << std::endl;
            return false;
        }
        
        int quantity = std::stoi(itemCheck[0][0]);
        
        // Удаление товара
        std::string query = 
            "DELETE FROM order_items WHERE order_id = " + std::to_string(orderId) + 
            " AND product_id = " + std::to_string(productId);
        
        db->executeNonQuery(query);
        
        // Возврат на склад
        db->executeNonQuery(
            "UPDATE products SET stock_quantity = stock_quantity + " + 
            std::to_string(quantity) + " WHERE product_id = " + std::to_string(productId)
        );
        
        // Обновление суммы
        db->executeNonQuery(
            "UPDATE orders SET total_price = COALESCE(("
            "SELECT SUM(quantity * price) FROM order_items WHERE order_id = " + 
            std::to_string(orderId) + "), 0) WHERE order_id = " + std::to_string(orderId)
        );
        
        std::cout << "✓ Товар #" << productId << " удален из заказа #" << orderId << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка удаления товара: " << e.what() << std::endl;
        return false;
    }
}

bool Customer::removeFromOrder(int orderId, int orderItemId) {
    std::cout << "Товар " << orderItemId << " удален из заказа " 
              << orderId << std::endl;
    return true;
}

std::vector<std::vector<std::string>> Customer::getMyOrdersFromDB() {
    try {
        return db->executeQuery(
            "SELECT order_id, status, total_price, order_date "
            "FROM orders WHERE user_id = " + std::to_string(getUserId()) + 
            " ORDER BY order_date DESC"
        );
    } catch (const std::exception& e) {
        std::cerr << "Ошибка получения заказов: " << e.what() << std::endl;
        return {};
    }
}

void Customer::viewMyOrders() {
    auto orders = getMyOrdersFromDB();
    
    if (orders.empty()) {
        std::cout << "У вас пока нет заказов" << std::endl;
        return;
    }
    
    std::cout << "\n=== Мои заказы ===\n";
    std::cout << std::left << std::setw(10) << "ID" 
              << std::setw(15) << "Статус" 
              << std::setw(15) << "Сумма" 
              << std::setw(20) << "Дата" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    for (const auto& row : orders) {
        std::cout << std::left << std::setw(10) << row[0]
                  << std::setw(15) << row[1]
                  << std::setw(15) << row[2]
                  << std::setw(20) << row[3] << std::endl;
    }
}

// std::string Customer::getOrderStatusFromDB(int orderId) {
//     try {
//         auto result = db->executeQuery(
//             "SELECT status FROM orders WHERE order_id = " + 
//             std::to_string(orderId) + " AND user_id = " + std::to_string(getUserId())
//         );
        
//         return result.empty() ? "Заказ не найден" : result[0][0];
//     } catch (const std::exception& e) {
//         return "Ошибка получения статуса";
//     }
// }
std::string Customer::getOrderStatusFromDB(int orderId) {
    try {
        // Используем функцию getOrderStatus из functions.sql
        auto result = db->executeQuery(
            "SELECT getOrderStatus(" + std::to_string(orderId) + ")"
        );
        
        if (result.empty() || result[0][0].empty()) {
            return "Статус не определен";
        }
        
        return result[0][0];
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка получения статуса: " << e.what() << std::endl;
        return "Ошибка";
    }
}

bool Customer::processReturnDB(int orderId) {
    try {
        // Используем функцию canReturnOrder из SQL
        auto canReturnResult = db->executeQuery(
            "SELECT canReturnOrder(" + std::to_string(orderId) + ")"
        );
        
        if (canReturnResult.empty() || canReturnResult[0][0] != "t") {
            std::cout << "Возврат невозможен" << std::endl;
            return false;
        }
        
        // Обновляем статус
        db->executeNonQuery(
            "UPDATE orders SET status = 'returned' WHERE order_id = " + 
            std::to_string(orderId)
        );
        
        // Возвращаем товары на склад
        db->executeNonQuery(
            "UPDATE products p "
            "SET stock_quantity = p.stock_quantity + oi.quantity "
            "FROM order_items oi "
            "WHERE p.product_id = oi.product_id "
            "AND oi.order_id = " + std::to_string(orderId)
        );
        
        std::cout << "✓ Возврат заказа #" << orderId << " оформлен" << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка возврата: " << e.what() << std::endl;
        return false;
    }
}

bool Customer::returnOrder(int orderId) {
    return processReturnDB(orderId);
}

void Customer::viewOrderStatusHistory(int orderId) {
    try {
        auto result = db->executeQuery(
            "SELECT old_status, new_status, changed_at "
            "FROM order_status_history WHERE order_id = " + 
            std::to_string(orderId) + " ORDER BY changed_at DESC"
        );
        
        if (result.empty()) {
            std::cout << "История изменений статуса для заказа #" << orderId << " не найдена" << std::endl;
            return;
        }
        
        std::cout << "\n=== История статусов заказа #" << orderId << " ===\n";
        std::cout << std::left << std::setw(15) << "Было" 
                  << std::setw(15) << "Стало" 
                  << std::setw(20) << "Дата изменения" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        
        for (const auto& row : result) {
            std::string oldStatus = row[0].empty() ? "—" : row[0];
            std::cout << std::left << std::setw(15) << oldStatus
                      << std::setw(15) << row[1]
                      << std::setw(20) << row[2] << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка получения истории: " << e.what() << std::endl;
    }
}

bool Customer::makePayment(int orderId, std::unique_ptr<PaymentStrategy> paymentStrategy) {
    std::cout << "Оплата заказа " << orderId << "..." << std::endl;
    
    try {
        // Получаем сумму заказа
        auto result = db->executeQuery(
            "SELECT total_price FROM orders WHERE order_id = " + 
            std::to_string(orderId) + " AND user_id = " + std::to_string(getUserId())
        );
        
        if (result.empty()) {
            std::cout << "Заказ не найден" << std::endl;
            return false;
        }
        
        double amount = std::stod(result[0][0]);
        
        if (paymentStrategy && paymentStrategy->pay(amount)) {
            // Обновляем статус заказа
            db->executeNonQuery(
                "UPDATE orders SET status = 'completed' WHERE order_id = " + 
                std::to_string(orderId)
            );
            
            std::cout << "✓ Заказ #" << orderId << " оплачен успешно" << std::endl;
            return true;
        }
        
        return false;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка оплаты: " << e.what() << std::endl;
        return false;
    }
}