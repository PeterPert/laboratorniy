#include "../include/Admin.h"
#include "../include/DatabaseConnection.h"
#include <iostream>
#include <iomanip>
#include <fstream>

Admin::Admin(int id, const std::string& name, const std::string& email)
    : User(id, name, email, "admin") {}

void Admin::displayMenu() {
    std::cout << "\n=== Меню администратора ===\n";
    std::cout << "1. Добавить новый продукт\n";
    std::cout << "2. Обновить информацию о продукте\n";
    std::cout << "3. Удалить продукт\n";
    std::cout << "4. Просмотр всех заказов\n";
    std::cout << "5. Просмотр деталей заказа\n";
    std::cout << "6. Изменить статус заказа\n";
    std::cout << "7. Просмотр истории статусов заказа\n";
    std::cout << "8. Просмотр журнала аудита\n";
    std::cout << "9. Сформировать отчёт (CSV)\n";
    std::cout << "10. Выход\n";
    std::cout << "Выберите действие: ";
}

bool Admin::hasPermission(const std::string& action) const {
    // Администратор имеет все права
    return true;
}

void Admin::addProduct(std::unique_ptr<Product> product) {
    // Логика добавления продукта в БД
    std::cout << "Продукт добавлен: " << product->getName() << std::endl;
}

bool Admin::updateProduct(int productId, const std::string& field, const std::string& value) {
    // Логика обновления продукта
    std::cout << "Продукт " << productId << " обновлен: " 
              << field << " = " << value << std::endl;
    return true;
}

bool Admin::deleteProduct(int productId) {
    // Логика удаления продукта
    std::cout << "Продукт " << productId << " удален" << std::endl;
    return true;
}

void Admin::viewAllOrders() {
    // Логика просмотра всех заказов
    std::cout << "Список всех заказов:" << std::endl;
}

bool Admin::updateOrderStatus(int orderId, const std::string& newStatus) {
    // Логика обновления статуса заказа
    std::cout << "Статус заказа " << orderId 
              << " изменен на: " << newStatus << std::endl;
    return true;
}

void Admin::viewOrderHistory(int orderId) {
    // Логика просмотра истории заказа
    std::cout << "История заказа " << orderId << ":" << std::endl;
}

void Admin::viewAuditLog() {
    // Логика просмотра журнала аудита
    std::cout << "Журнал аудита:" << std::endl;
}

void Admin::generateReport(const std::string& filename) {
    // Логика генерации CSV отчета
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "OrderID,Status,TotalPrice,OrderDate\n";
        file << "1,completed,100.50,2024-01-01\n";
        file.close();
        std::cout << "Отчет сохранен в " << filename << std::endl;
    }
}