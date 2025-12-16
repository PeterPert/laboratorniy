#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <map>
#include <pqxx/pqxx> // Библиотека для работы с PostgreSQL

// Структуры данных
struct Sale {
    int sale_id;
    std::string sale_date;
    int product_id;
    int customer_id;
    int quantity;
    double amount;
};

struct Product {
    int product_id;
    std::string product_name;
    std::string category;
    double price;
};

struct Customer {
    int customer_id;
    std::string customer_name;
    std::string region;
};

// Функция для преобразования даты в формат DATE
std::string convertToDateFormat(const std::string& date_str) {
    std::tm tm = {};
    std::istringstream ss(date_str);
    
    // Преобразование строки в структуру tm (формат: YYYY-MM-DD)
    ss >> std::get_time(&tm, "%Y-%m-%d");
    
    if (ss.fail()) {
        std::cerr << "Ошибка при преобразовании даты: " << date_str << std::endl;
        return "";
    }
    
    // Преобразуем tm обратно в строку для использования в запросах
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

// Функции для загрузки данных из CSV
std::vector<Sale> loadSalesData(const std::string& filename) {
    std::vector<Sale> sales;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return sales;
    }
    
    std::string line;
    std::getline(file, line); // Пропускаем заголовок
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Sale sale;
        std::string temp;
        
        // Чтение значений из CSV
        std::getline(ss, temp, ',');
        sale.sale_id = std::stoi(temp); // sale_id
        
        std::getline(ss, sale.sale_date, ','); // sale_date
        sale.sale_date = convertToDateFormat(sale.sale_date); // Трансформация даты
        
        std::getline(ss, temp, ',');
        sale.product_id = std::stoi(temp); // product_id
        
        std::getline(ss, temp, ',');
        sale.customer_id = std::stoi(temp); // customer_id
        
        std::getline(ss, temp, ',');
        sale.quantity = std::stoi(temp); // quantity
        
        std::getline(ss, temp, ',');
        sale.amount = std::stod(temp); // amount
        
        sales.push_back(sale);
    }
    
    file.close();
    return sales;
}

std::vector<Product> loadProductsData(const std::string& filename) {
    std::vector<Product> products;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return products;
    }
    
    std::string line;
    std::getline(file, line); // Пропускаем заголовок
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Product product;
        std::string temp;
        
        std::getline(ss, temp, ',');
        product.product_id = std::stoi(temp);
        
        std::getline(ss, product.product_name, ',');
        std::getline(ss, product.category, ',');
        
        std::getline(ss, temp, ',');
        product.price = std::stod(temp);
        
        products.push_back(product);
    }
    
    file.close();
    return products;
}

std::vector<Customer> loadCustomersData(const std::string& filename) {
    std::vector<Customer> customers;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return customers;
    }
    
    std::string line;
    std::getline(file, line); // Пропускаем заголовок
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Customer customer;
        std::string temp;
        
        std::getline(ss, temp, ',');
        customer.customer_id = std::stoi(temp);
        
        std::getline(ss, customer.customer_name, ',');
        std::getline(ss, customer.region, ',');
        
        customers.push_back(customer);
    }
    
    file.close();
    return customers;
}

// Функция для выполнения агрегации данных
struct SalesAggregation {
    std::string period; // Месяц или год-месяц
    double total_amount;
    int total_quantity;
    int transaction_count;
};

std::vector<SalesAggregation> aggregateSalesData(const std::vector<Sale>& sales) {
    std::map<std::string, SalesAggregation> aggregation;
    
    for (const auto& sale : sales) {
        // Извлекаем год и месяц из даты для агрегации
        std::string period = sale.sale_date.substr(0, 7); // YYYY-MM
        
        if (aggregation.find(period) == aggregation.end()) {
            aggregation[period] = SalesAggregation{period, 0.0, 0, 0};
        }
        
        aggregation[period].total_amount += sale.amount;
        aggregation[period].total_quantity += sale.quantity;
        aggregation[period].transaction_count++;
    }
    
    // Преобразуем map в vector
    std::vector<SalesAggregation> result;
    for (const auto& pair : aggregation) {
        result.push_back(pair.second);
    }
    
    return result;
}

// Функции для загрузки данных в PostgreSQL
void loadProductsToDB(pqxx::connection& conn, const std::vector<Product>& products) {
    pqxx::work txn(conn);
    
    try {
        for (const auto& product : products) {
            std::string sql = "INSERT INTO products_dim (product_id, product_name, category, price) "
                            "VALUES (" + std::to_string(product.product_id) + ", " +
                            txn.quote(product.product_name) + ", " +
                            txn.quote(product.category) + ", " +
                            std::to_string(product.price) + ")";
            
            txn.exec(sql);
        }
        
        txn.commit();
        std::cout << "Загружено " << products.size() << " товаров" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при загрузке товаров: " << e.what() << std::endl;
        txn.abort();
    }
}

void loadCustomersToDB(pqxx::connection& conn, const std::vector<Customer>& customers) {
    pqxx::work txn(conn);
    
    try {
        for (const auto& customer : customers) {
            std::string sql = "INSERT INTO customers_dim (customer_id, customer_name, region) "
                            "VALUES (" + std::to_string(customer.customer_id) + ", " +
                            txn.quote(customer.customer_name) + ", " +
                            txn.quote(customer.region) + ")";
            
            txn.exec(sql);
        }
        
        txn.commit();
        std::cout << "Загружено " << customers.size() << " клиентов" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при загрузке клиентов: " << e.what() << std::endl;
        txn.abort();
    }
}

void loadSalesToDB(pqxx::connection& conn, const std::vector<Sale>& sales) {
    pqxx::work txn(conn);
    
    try {
        for (const auto& sale : sales) {
            std::string sql = "INSERT INTO sales_fact (sale_id, sale_date, product_id, "
                            "customer_id, quantity, amount) "
                            "VALUES (" + std::to_string(sale.sale_id) + ", " +
                            txn.quote(sale.sale_date) + ", " +
                            std::to_string(sale.product_id) + ", " +
                            std::to_string(sale.customer_id) + ", " +
                            std::to_string(sale.quantity) + ", " +
                            std::to_string(sale.amount) + ")";
            
            txn.exec(sql);
        }
        
        txn.commit();
        std::cout << "Загружено " << sales.size() << " продаж" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при загрузке продаж: " << e.what() << std::endl;
        txn.abort();
    }
}

// Функции для выполнения аналитических запросов
void executeAnalyticalQueries(pqxx::connection& conn) {
    std::cout << "\n=== ВЫПОЛНЕНИЕ АНАЛИТИЧЕСКИХ ЗАПРОСОВ ===" << std::endl;
    
    try {
        // 1. Объем продаж по категориям товаров
        std::cout << "\n1. Объем продаж по категориям товаров:" << std::endl;
        pqxx::work txn1(conn);
        pqxx::result result1 = txn1.exec(
            "SELECT p.category, SUM(s.amount) AS total_sales "
            "FROM sales_fact s "
            "JOIN products_dim p ON s.product_id = p.product_id "
            "GROUP BY p.category "
            "ORDER BY total_sales DESC"
        );
        
        for (const auto& row : result1) {
            std::cout << "Категория: " << row["category"].c_str()
                     << ", Сумма продаж: " << row["total_sales"].c_str()
                     << std::endl;
        }
        txn1.commit();
        
        // 2. Количество покупок по регионам
        std::cout << "\n2. Количество покупок по регионам:" << std::endl;
        pqxx::work txn2(conn);
        pqxx::result result2 = txn2.exec(
            "SELECT c.region, COUNT(s.sale_id) AS number_of_sales "
            "FROM sales_fact s "
            "JOIN customers_dim c ON s.customer_id = c.customer_id "
            "GROUP BY c.region "
            "ORDER BY number_of_sales DESC"
        );
        
        for (const auto& row : result2) {
            std::cout << "Регион: " << row["region"].c_str()
                     << ", Количество продаж: " << row["number_of_sales"].c_str()
                     << std::endl;
        }
        txn2.commit();
        
        // 3. Средний чек за месяц
        std::cout << "\n3. Средний чек за месяц:" << std::endl;
        pqxx::work txn3(conn);
        pqxx::result result3 = txn3.exec(
            "SELECT EXTRACT(YEAR FROM sale_date) AS year, "
            "EXTRACT(MONTH FROM sale_date) AS month, "
            "AVG(amount) AS average_ticket "
            "FROM sales_fact "
            "GROUP BY EXTRACT(YEAR FROM sale_date), EXTRACT(MONTH FROM sale_date) "
            "ORDER BY year, month"
        );
        
        for (const auto& row : result3) {
            std::cout << "Год: " << row["year"].c_str()
                     << ", Месяц: " << row["month"].c_str()
                     << ", Средний чек: " << row["average_ticket"].c_str()
                     << std::endl;
        }
        txn3.commit();
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при выполнении аналитических запросов: " 
                 << e.what() << std::endl;
    }
}

// Основная функция программы
int main() {
    // Параметры подключения к PostgreSQL
    std::string connection_string = "dbname=CSW user=postgres password=qazwsxedc9 "
                                   "host=localhost port=5432";
    
    try {
        // Подключение к базе данных
        std::cout << "Подключение к PostgreSQL..." << std::endl;
        pqxx::connection conn(connection_string);
        
        if (conn.is_open()) {
            std::cout << "Успешное подключение к базе данных!" << std::endl;
            
            // 1. Извлечение данных из CSV файлов
            std::cout << "\n=== ИЗВЛЕЧЕНИЕ ДАННЫХ ИЗ CSV ФАЙЛОВ ===" << std::endl;
            std::string base_path = "C:/Users/petrt/OneDrive/Desktop/dz2/"; //добавлено отдельно 
            std::vector<Product> products = loadProductsData(base_path + "products.csv");
            std::cout << "Загружено " << products.size() << " товаров из CSV" << std::endl;
            
            std::vector<Customer> customers = loadCustomersData(base_path + "customers.csv");
            std::cout << "Загружено " << customers.size() << " клиентов из CSV" << std::endl;
            
            std::vector<Sale> sales = loadSalesData(base_path + "sales.csv");
            std::cout << "Загружено " << sales.size() << " продаж из CSV" << std::endl;
            
            // 2. Трансформация данных (выполняется внутри loadSalesData)
            std::cout << "\n=== ТРАНСФОРМАЦИЯ ДАННЫХ ===" << std::endl;
            std::cout << "Даты преобразованы в формат DATE" << std::endl;
            
            // Агрегация данных для анализа
            std::vector<SalesAggregation> aggregatedData = aggregateSalesData(sales);
            std::cout << "Агрегированные данные по " << aggregatedData.size() 
                     << " периодам созданы" << std::endl;
            
            // Вывод агрегированных данных
            std::cout << "\nАгрегированные данные по месяцам:" << std::endl;
            for (const auto& agg : aggregatedData) {
                std::cout << "Период: " << agg.period
                         << ", Сумма: " << agg.total_amount
                         << ", Количество: " << agg.total_quantity
                         << ", Транзакций: " << agg.transaction_count
                         << std::endl;
            }
            
            // 3. Загрузка данных в PostgreSQL
            std::cout << "\n=== ЗАГРУЗКА ДАННЫХ В POSTGRESQL ===" << std::endl;
            
            // Очистка таблиц перед загрузкой (опционально)
            pqxx::work cleanup(conn);
            cleanup.exec("TRUNCATE TABLE sales_fact RESTART IDENTITY CASCADE");
            cleanup.exec("TRUNCATE TABLE products_dim RESTART IDENTITY CASCADE");
            cleanup.exec("TRUNCATE TABLE customers_dim RESTART IDENTITY CASCADE");
            cleanup.commit();
            std::cout << "Таблицы очищены" << std::endl;
            
            // Загрузка данных в порядке зависимостей
            loadProductsToDB(conn, products);
            loadCustomersToDB(conn, customers);
            loadSalesToDB(conn, sales);
            
            // 4. Выполнение аналитических запросов
            executeAnalyticalQueries(conn);
            
            std::cout << "\nПрограмма успешно завершена!" << std::endl;
            
        } else {
            std::cerr << "Не удалось подключиться к базе данных" << std::endl;
            return 1;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}