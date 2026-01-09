#include "../include/DatabaseConnection.h"
#include "../include/User.h"
#include "../include/Admin.h"
#include "../include/Manager.h"
#include "../include/Customer.h"
#include "../include/Logger.h"
#include "../include/Utils.h"
#include "../include/BankCardPayment.h"
#include "../include/DigitalWalletPayment.h"
#include "../include/SBPPayment.h"
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>

// Вспомогательный класс для работы с SQL функциями
class DatabaseHelper {
public:
    static std::string getOrderStatus(std::shared_ptr<DatabaseConnection<std::string>> db, 
                                      int orderId) {
        try {
            auto result = db->executeQuery(
                "SELECT getOrderStatus(" + std::to_string(orderId) + ")"
            );
            return result.empty() ? "неизвестно" : result[0][0];
        } catch (...) {
            return "ошибка";
        }
    }
    
    static bool canReturnOrder(std::shared_ptr<DatabaseConnection<std::string>> db, 
                               int orderId) {
        try {
            auto result = db->executeQuery(
                "SELECT canReturnOrder(" + std::to_string(orderId) + ")"
            );
            return !result.empty() && result[0][0] == "t";
        } catch (...) {
            return false;
        }
    }
    
    static double getTotalSpentByUser(std::shared_ptr<DatabaseConnection<std::string>> db, 
                                      int userId) {
        try {
            auto result = db->executeQuery(
                "SELECT getTotalSpentByUser(" + std::to_string(userId) + ")"
            );
            return result.empty() ? 0.0 : std::stod(result[0][0]);
        } catch (...) {
            return 0.0;
        }
    }
};

// Функция для загрузки SQL файлов
void loadSQLFiles(std::shared_ptr<DatabaseConnection<std::string>> db) {
    std::vector<std::string> sqlFiles = {
        "sql/functions.sql",
        "sql/procedures.sql",
        "sql/triggers.sql"
    };
    
    for (const auto& filename : sqlFiles) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string sql((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
            try {
                db->executeNonQuery(sql);
                std::cout << "Файл " << filename << " загружен успешно" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Ошибка загрузки " << filename << ": " << e.what() << std::endl;
            }
            file.close();
        }
    }
}

// Инициализация БД
void initializeDatabase(std::shared_ptr<DatabaseConnection<std::string>> db) {
    try {
        // Проверяем есть ли пользователи
        auto result = db->executeQuery("SELECT COUNT(*) FROM users");
        
        if (result.empty() || std::stoi(result[0][0]) == 0) {
            std::cout << "Инициализация тестовых данных..." << std::endl;
            
            db->executeNonQuery(
                "INSERT INTO users (user_id, name, email, role, password_hash, loyalty_level) VALUES "
                "(1, 'Администратор', 'admin@store.com', 'admin', 'hash1', 0),"
                "(2, 'Менеджер', 'manager@store.com', 'manager', 'hash2', 0),"
                "(3, 'Покупатель', 'customer@store.com', 'customer', 'hash3', 1)"
            );
            
            db->executeNonQuery(
                "INSERT INTO products (product_id, name, price, stock_quantity) VALUES "
                "(1, 'Ноутбук', 50000.00, 10),"
                "(2, 'Смартфон', 30000.00, 20),"
                "(3, 'Наушники', 5000.00, 30)"
            );
            
            std::cout << "Тестовые данные созданы успешно" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка инициализации БД: " << e.what() << std::endl;
    }
}

// Создание тестовых пользователей (без DatabaseConnection в конструкторах)
// std::unique_ptr<User> createTestUser(const std::string& role) {
//     if (role == "admin") {
//         return std::make_unique<Admin>(1, "Admin User", "admin@store.com");
//     } else if (role == "manager") {
//         return std::make_unique<Manager>(2, "Manager User", "manager@store.com");
//     } else if (role == "customer") {
//         return std::make_unique<Customer>(3, "Customer User", "customer@store.com", 1);
//     }
//     return nullptr;
// }
std::unique_ptr<User> createTestUser(const std::string& role, 
                                     std::shared_ptr<DatabaseConnection<std::string>> db) {
    if (role == "admin") {
        return std::make_unique<Admin>(1, "Admin User", "admin@store.com");
    // } else if (role == "manager") {
    //     return std::make_unique<Manager>(2, "Manager User", "manager@store.com");
    } else if (role == "manager") {
        return std::make_unique<Manager>(2, "Manager User", "manager@store.com", db);
    } else if (role == "customer") {
        return std::make_unique<Customer>(3, "Customer User", "customer@store.com", 1, db);
    }
    return nullptr;
}
// Обработка меню администратора
void handleAdminMenu(std::unique_ptr<User>& user, 
                     std::shared_ptr<DatabaseConnection<std::string>> db,
                     std::shared_ptr<Logger> logger) {
    auto admin = dynamic_cast<Admin*>(user.get());
    if (!admin) return;
    
    int choice;
    bool running = true;
    
    while (running) {
        admin->displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: { // Добавить продукт
                std::string name;
                double price;
                int quantity;
                
                std::cout << "Введите название продукта: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Введите цену: ";
                std::cin >> price;
                std::cout << "Введите количество: ";
                std::cin >> quantity;
                
                try {
                    auto result = db->executeQuery("SELECT COALESCE(MAX(product_id), 0) + 1 FROM products");
                    int nextId = result.empty() ? 1 : std::stoi(result[0][0]);
                    
                    std::string query = "INSERT INTO products (product_id, name, price, stock_quantity) VALUES (" +
                                       std::to_string(nextId) + ", '" + name + "', " + 
                                       std::to_string(price) + ", " + std::to_string(quantity) + ")";
                    
                    db->executeNonQuery(query);
                    std::cout << "✓ Продукт добавлен: " << name << " (ID: " << nextId << ")" << std::endl;
                    
                    logger->logAction(admin->getUserId(), "product", nextId, "insert");
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            
            case 2: { // Обновить продукт
                int productId;
                std::string field, value;
                
                std::cout << "Введите ID продукта: ";
                std::cin >> productId;
                std::cout << "Введите поле для обновления (name/price/stock_quantity): ";
                std::cin >> field;
                std::cout << "Введите новое значение: ";
                std::cin.ignore();
                std::getline(std::cin, value);
                
                try {
                    std::string query;
                    if (field == "name") {
                        query = "UPDATE products SET name = '" + value + "' WHERE product_id = " + std::to_string(productId);
                    } else if (field == "price") {
                        query = "UPDATE products SET price = " + value + " WHERE product_id = " + std::to_string(productId);
                    } else if (field == "stock_quantity") {
                        query = "UPDATE products SET stock_quantity = " + value + " WHERE product_id = " + std::to_string(productId);
                    } else {
                        std::cout << "Неверное поле" << std::endl;
                        break;
                    }
                    
                    db->executeNonQuery(query);
                    std::cout << "✓ Продукт обновлен" << std::endl;
                    logger->logAction(admin->getUserId(), "product", productId, "update");
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            
            case 3: { // Удалить продукт
                int productId;
                std::cout << "Введите ID продукта для удаления: ";
                std::cin >> productId;
                
                try {
                    auto result = db->executeQuery(
                        "SELECT name FROM products WHERE product_id = " + std::to_string(productId)
                    );
                    
                    if (result.empty()) {
                        std::cout << "Продукт не найден" << std::endl;
                        break;
                    }
                    
                    std::cout << "Удалить продукт \"" << result[0][0] << "\"? (y/n): ";
                    char confirm;
                    std::cin >> confirm;
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        std::string query = "DELETE FROM products WHERE product_id = " + 
                                           std::to_string(productId);
                        db->executeNonQuery(query);
                        std::cout << "✓ Продукт удален" << std::endl;
                        logger->logAction(admin->getUserId(), "product", productId, "delete");
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            
            case 4: { // Просмотр всех заказов
                try {
                    auto result = db->executeQuery(
                        "SELECT o.order_id, u.name, o.status, o.total_price, o.order_date "
                        "FROM orders o JOIN users u ON o.user_id = u.user_id "
                        "ORDER BY o.order_date DESC"
                    );
                    
                    std::cout << "\n=== Список всех заказов ===\n";
                    if (result.empty()) {
                        std::cout << "Заказов нет" << std::endl;
                        break;
                    }
                    
                    std::cout << std::left << std::setw(10) << "ID" 
                              << std::setw(20) << "Пользователь" 
                              << std::setw(15) << "Статус" 
                              << std::setw(15) << "Сумма" 
                              << std::setw(20) << "Дата" << std::endl;
                    std::cout << std::string(80, '-') << std::endl;
                    
                    for (const auto& row : result) {
                        std::cout << std::left << std::setw(10) << row[0]
                                  << std::setw(20) << row[1]
                                  << std::setw(15) << row[2]
                                  << std::setw(15) << row[3]
                                  << std::setw(20) << row[4] << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            
            case 6: { // Изменить статус заказа
                int orderId;
                std::string newStatus;
                
                std::cout << "Введите ID заказа: ";
                std::cin >> orderId;
                std::cout << "Введите новый статус (pending/completed/canceled/returned): ";
                std::cin >> newStatus;
                
                try {
                    std::string query = "UPDATE orders SET status = '" + newStatus + 
                                       "' WHERE order_id = " + std::to_string(orderId);
                    db->executeNonQuery(query);
                    std::cout << "✓ Статус обновлен" << std::endl;
                    logger->logAction(admin->getUserId(), "order", orderId, "update");
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            
            case 8: { // Просмотр журнала аудита
                try {
                    auto result = db->executeQuery(
                        "SELECT al.log_id, al.entity_type, al.entity_id, al.operation, "
                        "u.name, al.performed_at "
                        "FROM audit_log al "
                        "JOIN users u ON al.performed_by = u.user_id "
                        "ORDER BY al.performed_at DESC "
                        "LIMIT 50"
                    );
                    
                    std::cout << "\n=== Журнал аудита (последние 50 записей) ===\n";
                    if (result.empty()) {
                        std::cout << "Записей нет" << std::endl;
                        break;
                    }
                    
                    std::cout << std::left << std::setw(8) << "ID" 
                              << std::setw(10) << "Тип" 
                              << std::setw(8) << "Объект" 
                              << std::setw(10) << "Операция" 
                              << std::setw(20) << "Пользователь" 
                              << std::setw(20) << "Дата" << std::endl;
                    std::cout << std::string(76, '-') << std::endl;
                    
                    for (const auto& row : result) {
                        std::cout << std::left << std::setw(8) << row[0]
                                  << std::setw(10) << row[1]
                                  << std::setw(8) << row[2]
                                  << std::setw(10) << row[3]
                                  << std::setw(20) << row[4]
                                  << std::setw(20) << row[5] << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            
            case 9: { // Сформировать отчет
                std::cout << "\n=== Формирование CSV отчета ===\n";
                
                // Создаем директорию если не существует
                std::filesystem::create_directory("reports");
                
                std::string filename = "C:/Users/petrt/OneDrive/Desktop/exam_good/reports/audit_report_" + 
                          std::to_string(time(nullptr)) + ".csv";
                
                try {
                    std::ofstream file(filename);
                    if (!file) {
                        std::cerr << "Ошибка создания файла: " << filename << std::endl;
                        break;
                    }
                    
                    // Простой отчет с тремя таблицами
                    file << "=== АУДИТ ЛОГ ===\n";
                    file << "Тип объекта,ID объекта,Операция,Пользователь,Дата\n";
                    
                    auto auditData = db->executeQuery(
                        "SELECT entity_type, entity_id, operation, "
                        "(SELECT name FROM users WHERE user_id = al.performed_by), "
                        "performed_at "
                        "FROM audit_log al "
                        "ORDER BY performed_at DESC"
                    );
                    
                    for (const auto& row : auditData) {
                        file << row[0] << "," << row[1] << "," << row[2] << "," 
                            << row[3] << "," << row[4] << "\n";
                    }
                    
                    file << "\n=== ЗАКАЗЫ ===\n";
                    file << "ID заказа,Пользователь,Статус,Сумма,Дата\n";
                    
                    auto ordersData = db->executeQuery(
                        "SELECT o.order_id, u.name, o.status, o.total_price, o.order_date "
                        "FROM orders o JOIN users u ON o.user_id = u.user_id "
                        "ORDER BY o.order_date DESC"
                    );
                    
                    for (const auto& row : ordersData) {
                        file << row[0] << "," << row[1] << "," << row[2] << "," 
                            << row[3] << "," << row[4] << "\n";
                    }
                    
                    file << "\n=== ИСТОРИЯ СТАТУСОВ ===\n";
                    file << "ID заказа,Старый статус,Новый статус,Дата изменения,Кто изменил\n";
                    
                    auto historyData = db->executeQuery(
                        "SELECT osh.order_id, osh.old_status, osh.new_status, "
                        "osh.changed_at, u.name "
                        "FROM order_status_history osh "
                        "JOIN users u ON osh.changed_by = u.user_id "
                        "ORDER BY osh.changed_at DESC"
                    );
                    
                    for (const auto& row : historyData) {
                        file << row[0] << "," << row[1] << "," << row[2] << "," 
                            << row[3] << "," << row[4] << "\n";
                    }
                    
                    file.close();
                    
                    std::cout << "✓ Отчет создан: " << filename << std::endl;
                    std::cout << "Содержит данные из:\n";
                    std::cout << "- Аудит лог: " << auditData.size() << " записей\n";
                    std::cout << "- Заказы: " << ordersData.size() << " записей\n";
                    std::cout << "- История статусов: " << historyData.size() << " записей\n";
                    
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            
            case 10: // Выход
                running = false;
                std::cout << "Выход из меню администратора" << std::endl;
                break;
                
            case 5: { // Детали заказа
                int orderId;
                std::cout << "Введите ID заказа для просмотра деталей: ";
                std::cin >> orderId;
                
                try {
                    // Получаем основную информацию о заказе
                    auto orderInfo = db->executeQuery(
                        "SELECT o.order_id, u.name, u.email, o.status, o.total_price, o.order_date "
                        "FROM orders o "
                        "JOIN users u ON o.user_id = u.user_id "
                        "WHERE o.order_id = " + std::to_string(orderId)
                    );
                    
                    if (orderInfo.empty()) {
                        std::cout << "Заказ с ID " << orderId << " не найден." << std::endl;
                        break;
                    }
                    
                    std::cout << "\n=== Детали заказа ID: " << orderId << " ===\n";
                    std::cout << "Пользователь: " << orderInfo[0][1] << std::endl;
                    std::cout << "Email: " << orderInfo[0][2] << std::endl;
                    std::cout << "Статус: " << orderInfo[0][3] << std::endl;
                    std::cout << "Общая сумма: " << orderInfo[0][4] << " руб." << std::endl;
                    std::cout << "Дата заказа: " << orderInfo[0][5] << std::endl;
                    
                    // Получаем элементы заказа
                    auto orderItems = db->executeQuery(
                        "SELECT p.name, oi.quantity, oi.price, (oi.quantity * oi.price) as total "
                        "FROM order_items oi "
                        "JOIN products p ON oi.product_id = p.product_id "
                        "WHERE oi.order_id = " + std::to_string(orderId) + " "
                        "ORDER BY oi.order_item_id"
                    );
                    
                    std::cout << "\n=== Состав заказа ===\n";
                    if (orderItems.empty()) {
                        std::cout << "Заказ пуст." << std::endl;
                    } else {
                        std::cout << std::left << std::setw(30) << "Продукт" 
                                  << std::setw(10) << "Кол-во" 
                                  << std::setw(15) << "Цена за шт." 
                                  << std::setw(15) << "Сумма" << std::endl;
                        std::cout << std::string(70, '-') << std::endl;
                        
                        double total = 0;
                        for (const auto& item : orderItems) {
                            std::cout << std::left << std::setw(30) << item[0]
                                      << std::setw(10) << item[1]
                                      << std::setw(15) << item[2] + " руб."
                                      << std::setw(15) << item[3] + " руб." << std::endl;
                            total += std::stod(item[3]);
                        }
                        std::cout << std::string(70, '-') << std::endl;
                        std::cout << std::left << std::setw(55) << "ИТОГО:"
                                  << std::setw(15) << std::to_string(total) + " руб." << std::endl;
                    }
                    
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка при получении деталей заказа: " << e.what() << std::endl;
                }
                break;
            }
            case 7: { // История статусов заказа с использованием функции getHistory
                int orderId;
                std::cout << "Введите ID заказа для просмотра истории статусов: ";
                std::cin >> orderId;
                
                try {
                    // Сначала проверяем существование заказа
                    auto orderCheck = db->executeQuery(
                        "SELECT order_id FROM orders WHERE order_id = " + std::to_string(orderId)
                    );
                    
                    if (orderCheck.empty()) {
                        std::cout << "Заказ с ID " << orderId << " не найден." << std::endl;
                        break;
                    }
                    
                    // Используем функцию getHistory из базы данных
                    auto history = db->executeQuery(
                        "SELECT * FROM getHistory(" + std::to_string(orderId) + ")"
                    );
                    
                    std::cout << "\n=== История статусов заказа ID: " << orderId << " ===\n";
                    
                    if (history.empty()) {
                        std::cout << "История статусов для данного заказа отсутствует." << std::endl;
                    } else {
                        std::cout << std::left << std::setw(15) << "Старый статус" 
                                  << std::setw(15) << "Новый статус" 
                                  << std::setw(25) << "Дата изменения" 
                                  << std::setw(20) << "Изменил (ID)" << std::endl;
                        std::cout << std::string(75, '-') << std::endl;
                        
                        for (const auto& row : history) {
                            std::string oldStatus = row[0].empty() ? "N/A" : row[0];
                            std::string userName = "Пользователь " + row[3];
                            
                            // Пытаемся получить имя пользователя
                            try {
                                auto userInfo = db->executeQuery(
                                    "SELECT name FROM users WHERE user_id = " + row[3]
                                );
                                if (!userInfo.empty()) {
                                    userName = userInfo[0][0];
                                }
                            } catch (...) {
                                // Если не удалось получить имя, используем ID
                            }
                            
                            std::cout << std::left << std::setw(15) << oldStatus
                                      << std::setw(15) << row[1]
                                      << std::setw(25) << row[2]
                                      << std::setw(20) << userName << std::endl;
                        }
                        
                        // Также показываем текущий статус
                        auto currentStatus = db->executeQuery(
                            "SELECT status FROM orders WHERE order_id = " + std::to_string(orderId)
                        );
                        
                        if (!currentStatus.empty()) {
                            std::cout << "\nТекущий статус: " << currentStatus[0][0] << std::endl;
                        }
                    }
                    
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка при получении истории статусов: " << e.what() << std::endl;
                    std::cout << "Примечание: Убедитесь, что функция getHistory существует в базе данных." << std::endl;
                }
                break;
            }
                
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void handleManagerMenu(std::unique_ptr<User>& user, 
                      std::shared_ptr<DatabaseConnection<std::string>> db,
                      std::shared_ptr<Logger> logger) {
    auto manager = dynamic_cast<Manager*>(user.get());
    if (!manager) {
        std::cout << "Ошибка: пользователь не является менеджером" << std::endl;
        return;
    }
    
    int choice;
    bool running = true;
    
    while (running) {
        manager->displayMenu();
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Пожалуйста, введите число." << std::endl;
            continue;
        }
        
        switch (choice) {
            case 1: // Просмотр заказов в ожидании утверждения
                manager->viewPendingOrders();
                break;
                
            case 2: { // Утвердить заказ
                int orderId;
                std::cout << "Введите ID заказа для утверждения: ";
                
                if (!(std::cin >> orderId)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Неверный ввод ID." << std::endl;
                    break;
                }
                
                if (manager->approveOrder(orderId)) {
                    logger->logAction(manager->getUserId(), "order", orderId, "update");
                    std::cout << "Действие залогировано." << std::endl;
                }
                break;
            }
                
            case 3: { // Обновить количество товара на складе
                int productId, newQuantity;
                
                std::cout << "\n=== Обновление количества товара на складе ===\n";
                
                // Сначала покажем список всех товаров
                try {
                    auto products = db->executeQuery(
                        "SELECT product_id, name, stock_quantity, price "
                        "FROM products ORDER BY product_id"
                    );
                    
                    if (!products.empty()) {
                        std::cout << "\nСписок товаров:\n";
                        std::cout << std::left << std::setw(10) << "ID" 
                                  << std::setw(25) << "Название" 
                                  << std::setw(15) << "На складе" 
                                  << std::setw(15) << "Цена" << std::endl;
                        std::cout << std::string(65, '-') << std::endl;
                        
                        for (const auto& row : products) {
                            std::cout << std::left << std::setw(10) << row[0]
                                      << std::setw(25) << (row[1].length() > 24 ? row[1].substr(0, 24) + "..." : row[1])
                                      << std::setw(15) << row[2]
                                      << std::setw(15) << row[3] << std::endl;
                        }
                        std::cout << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка загрузки списка товаров: " << e.what() << std::endl;
                }
                
                std::cout << "Введите ID товара: ";
                if (!(std::cin >> productId)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Неверный ввод ID товара." << std::endl;
                    break;
                }
                
                std::cout << "Введите новое количество: ";
                if (!(std::cin >> newQuantity)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Неверный ввод количества." << std::endl;
                    break;
                }
                
                if (manager->updateStock(productId, newQuantity)) {
                    logger->logAction(manager->getUserId(), "product", productId, "update");
                    std::cout << "Действие залогировано." << std::endl;
                }
                break;
            }
                
            case 4: { // Просмотр деталей заказа
                int orderId;
                std::cout << "Введите ID заказа: ";
                
                if (!(std::cin >> orderId)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Неверный ввод ID заказа." << std::endl;
                    break;
                }
                
                manager->viewOrderDetails(orderId);
                break;
            }
                
            case 5: { // Изменить статус заказа
                int orderId;
                std::string newStatus;
                
                std::cout << "Введите ID заказа: ";
                if (!(std::cin >> orderId)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Неверный ввод ID заказа." << std::endl;
                    break;
                }
                
                std::cout << "Введите новый статус (pending/completed/canceled/returned): ";
                std::cin >> newStatus;
                
                // Проверяем корректность статуса
                if (newStatus != "pending" && newStatus != "completed" && 
                    newStatus != "canceled" && newStatus != "returned") {
                    std::cout << "Неверный статус. Допустимые значения: pending, completed, canceled, returned" << std::endl;
                    break;
                }
                
                if (manager->updateOrderStatus(orderId, newStatus)) {
                    logger->logAction(manager->getUserId(), "order", orderId, "update");
                    std::cout << "Действие залогировано." << std::endl;
                }
                break;
            }
                
            case 6: // Просмотр истории утверждённых заказов
                manager->viewApprovedOrdersHistory();
                break;
                
            case 7: { // Просмотр истории статусов заказов
                int orderId;
                std::cout << "Введите ID заказа: ";
                
                if (!(std::cin >> orderId)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Неверный ввод ID заказа." << std::endl;
                    break;
                }
                
                manager->viewOrderStatusHistory(orderId);
                break;
            }
                
            case 8: // Выход
                running = false;
                std::cout << "Выход из меню менеджера." << std::endl;
                break;
                
            default:
                std::cout << "Неверный выбор. Пожалуйста, выберите пункт от 1 до 8." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Обработка меню покупателя
void handleCustomerMenu(std::unique_ptr<User>& user, 
                       std::shared_ptr<DatabaseConnection<std::string>> db,
                       std::shared_ptr<Logger> logger) {
    auto customer = dynamic_cast<Customer*>(user.get());
    if (!customer) return;
    
    int choice;
    bool running = true;
    
    while (running) {
        customer->displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: { // Создать новый заказ
                auto order = customer->createOrder();
                if (order) {
                    logger->logAction(customer->getUserId(), "order", 
                                     order->getOrderId(), "insert");
                }
                break;
            }
            
            case 2: { // Добавить товар в заказ
                int orderId, productId, quantity;
                
                std::cout << "\n=== Добавление товара в заказ ===\n";
                std::cout << "Введите ID заказа: ";
                std::cin >> orderId;
                std::cout << "Введите ID товара: ";
                std::cin >> productId;
                std::cout << "Введите количество: ";
                std::cin >> quantity;
                
                if (customer->addProductToOrderDB(orderId, productId, quantity)) {
                    logger->logAction(customer->getUserId(), "product", 
                                     productId, "insert");
                }
                break;
            }
            
            case 3: { // Удалить товар из заказа
                int orderId, productId;
                
                std::cout << "\n=== Удаление товара из заказа ===\n";
                std::cout << "Введите ID заказа: ";
                std::cin >> orderId;
                std::cout << "Введите ID товара: ";
                std::cin >> productId;
                
                if (customer->removeProductFromOrderDB(orderId, productId)) {
                    logger->logAction(customer->getUserId(), "product", 
                                     productId, "delete");
                }
                break;
            }
            
            case 4: // Просмотр моих заказов
                customer->viewMyOrders();
                break;
            
            case 5: { // Просмотр статуса заказа
                int orderId;
                std::cout << "Введите ID заказа: ";
                std::cin >> orderId;
                
                std::string status = customer->getOrderStatusFromDB(orderId);
                std::cout << "Статус заказа #" << orderId << ": " << status << std::endl;
                break;
            }
            
            case 6: { // Оплатить заказ
                int orderId;
                std::cout << "Введите ID заказа для оплаты: ";
                std::cin >> orderId;
                
                int paymentMethod;
                std::cout << "Выберите метод оплаты:\n";
                std::cout << "1. Банковская карта\n";
                std::cout << "2. Электронный кошелек\n";
                std::cout << "3. СБП\n";
                std::cout << "Выберите: ";
                std::cin >> paymentMethod;
                
                std::unique_ptr<PaymentStrategy> strategy;
                if (paymentMethod == 1) {
                    strategy = std::make_unique<BankCardPayment>("1234567812345678", "12/25", "123");
                } else if (paymentMethod == 2) {
                    strategy = std::make_unique<DigitalWalletPayment>("wallet123", "+79123456789");
                } else if (paymentMethod == 3) {
                    strategy = std::make_unique<SBPPayment>("Сбербанк", "+79123456789");
                } else {
                    std::cout << "Неверный метод оплаты" << std::endl;
                    break;
                }
                
                if (customer->makePayment(orderId, std::move(strategy))) {
                    logger->logAction(customer->getUserId(), "order", orderId, "update");
                }
                break;
            }
            
            case 7: { // Оформить возврат заказа
                int orderId;
                std::cout << "Введите ID заказа для возврата: ";
                std::cin >> orderId;
                
                if (customer->returnOrder(orderId)) {
                    logger->logAction(customer->getUserId(), "order", orderId, "update");
                }
                break;
            }
            
            case 8: { // Просмотр истории статусов заказа
                int orderId;
                std::cout << "Введите ID заказа: ";
                std::cin >> orderId;
                
                customer->viewOrderStatusHistory(orderId);
                break;
            }
            
            case 9: // Выход
                running = false;
                std::cout << "Выход из меню покупателя" << std::endl;
                break;
                
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main() {
    try {
        // Подключение к базе данных
        std::string connStr = "host=localhost port=5432 dbname=online-store user=postgres password=qazwsxedc9";
        auto db = std::make_shared<DatabaseConnection<std::string>>(connStr);
        
        // Инициализация БД
        initializeDatabase(db);
        
        // Загрузка SQL функций и триггеров
        loadSQLFiles(db);
        
        // Создание логгера
        auto logger = std::make_shared<Logger>(db);
        
        // Главное меню
        bool running = true;
        
        while (running) {
            std::cout << "\n=== Интернет-магазин ===\n";
            std::cout << "1. Войти как Администратор\n";
            std::cout << "2. Войти как Менеджер\n";
            std::cout << "3. Войти как Покупатель\n";
            std::cout << "4. Выход\n";
            std::cout << "Выберите роль: ";
            
            int roleChoice;
            std::cin >> roleChoice;
            
            std::unique_ptr<User> user;
            
            // В функции main исправьте вызовы:
            switch (roleChoice) {
                case 1:
                    user = createTestUser("admin", db);  // передаем db
                    if (user) handleAdminMenu(user, db, logger);
                    break;
                case 2:
                    user = createTestUser("manager", db);  // передаем db
                    if (user) handleManagerMenu(user, db, logger);
                    break;
                case 3:
                    user = createTestUser("customer", db);  // передаем db
                    if (user) handleCustomerMenu(user, db, logger);
                    break;
                case 4:
                    running = false;
                    std::cout << "Выход из программы" << std::endl;
                    break;
                default:
                    std::cout << "Неверный выбор" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}