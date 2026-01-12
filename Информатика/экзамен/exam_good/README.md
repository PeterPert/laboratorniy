#### **Описание задачи**



##### Цель работы

Разработка консольной системы управления интернет-магазином с поддержкой многопользовательского доступа, управлением заказами, товарами и автоматическим аудитом действий пользователей.

##### 

##### Краткое описание реализованной системы

Система представляет собой консольное приложение на C++ с архитектурой клиент-сервер, где серверная часть реализована на PostgreSQL. Система поддерживает три типа пользователей: покупатели, менеджеры и администраторы, каждый со своими правами доступа и функционалом.

##### 

##### Используемые технологии

Язык программирования: C++

База данных: PostgreSQL

Библиотека для работы с БД: libpqxx

Система сборки: CMake

Операционная система: Windows/Linux/macOS

#### 

#### **Архитектура проекта**



##### Описание классов и их взаимосвязей

User (абстрактный)

├── Customer (покупатель)

├── Manager (менеджер)

└── Admin (администратор)



Product (товар)

Order (заказ)

├── OrderItem (позиция заказа)

Payment (платёж)

└── PaymentStrategy (стратегия оплаты)

    ├── BankCardPayment

    ├── DigitalWalletPayment

    └── SBPPayment



DatabaseConnection<T> (шаблонный класс для работы с БД)





##### Применение принципов ООП



Наследование:

class Admin : public User { ... };

class BankCardPayment : public PaymentStrategy { ... };



Полиморфизм:

virtual void displayMenu() = 0;  // чисто виртуальная функция

virtual bool hasPermission(const std::string\& action) const = 0;



Композиция:

class Order {

private:

    std::vector<std::unique\_ptr<OrderItem>> items;  // композиция

};



Агрегация:

class Customer : public User {

private:

    std::shared\_ptr<DatabaseConnection<[std::string](std::string)>> db;  // агрегация

};



##### Использование шаблонного класса DatabaseConnection<T>



Шаблонный класс DatabaseConnection обеспечивает типобезопасное подключение к PostgreSQL:

template<typename T>

class DatabaseConnection {

    // T используется для будущих расширений

    std::unique\_ptr<[pqxx::connection](pqxx::connection)> conn;

    // ... методы для работы с БД

};



#### **Работа с базой данных**



##### структура базы данных

-таблицы
-функции

-процедуры

-тригеры



##### Список таблиц

1. users
2. products
3. orders
4. order\_items
5. order\_status\_history
6. audit\_log



##### Описание хранимых процедур, функций и триггеров


Хранимые функции:

getOrderStatus(order\_id) - возвращает текущий статус заказа

getUserOrderCount() - статистика заказов по пользователям

getTotalSpentByUser(user\_id) - общая сумма покупок пользователя

canReturnOrder(order\_id) - проверка возможности возврата заказа

getAuditLogByUser(user\_id) - логи действий пользователя

getOrderStatusHistory(order\_id)(gethistory(p\_order\_id)) - история изменения статусов





Хранимая процедура:

createOrder(user\_id, product\_id, quantity) - создание заказа в транзакции

updateOrderStatus(p\_order\_id,p\_new\_status,p\_user\_id) - изменение статуса



Триггеры:

product\_log, order\_log, user\_log - автоматическое логирование операций

trg\_order\_date\_update - обновление даты при изменении статуса

trg\_log\_status - запись истории изменений статусов

trg\_update\_totals - пересчёт сумм заказов при изменении цен



##### Механизм транзакций и отката при ошибках



Класс DatabaseConnection предоставляет методы для управления транзакциями:

void beginTransaction(); //начало транзакции

void commitTransaction(); //фиксация изменений

void rollbackTransaction(); // откат транзакции

bool isTransactionActive() const; //проверка активности

 

механизм отката:
template<typename T>

void DatabaseConnection<T>::rollbackTransaction() {

    try {

        if (transaction) {

            transaction->abort();

            transaction.reset();

        }

    } catch (const std::exception\& e) {

        throw std::runtime\_error("Ошибка отката транзакции: " + std::string(e.what()));

    }

}



Пример использования в Customer::addProductToOrderDB:

// Внутренняя транзакция через executeNonQuery

db->executeNonQuery("INSERT INTO order\_items ...");

db->executeNonQuery("UPDATE products SET stock\_quantity ...");

db->executeNonQuery("UPDATE orders SET total\_price ...");



#### **Умные указатели и STL**



##### Использование std::unique\_ptr и std::shared\_ptr



std::unique\_ptr (эксклюзивное владение):

// В классе Order

std::vector<std::unique\_ptr<OrderItem>> items;

// В классе Payment

std::unique\_ptr<PaymentStrategy> paymentStrategy;

// Создание стратегии оплаты

auto strategy = std::make\_unique<BankCardPayment>("1234567812345678", "12/25", "123");



std::shared\_ptr (разделяемое владение):

// В классе Customer

std::shared\_ptr<DatabaseConnection<[std::string](std::string)>> db;

// Создание подключения к БД

auto db = std::make\_shared<DatabaseConnection<[std::string](std::string)>>(connStr);



##### Примеры использования STL алгоритмов



std::find\_if с лямбда-выражением:

auto it = std::find\_if(orders.begin(), orders.end(),

    \[orderId](const std::shared\_ptr<Order>\& order) {

        return order->getOrderId() == orderId;

    });



std::copy\_if для фильтрации:

std::vector<std::shared\_ptr<Order>> filteredOrders;

std::copy\_if(orders.begin(), orders.end(),

             std::back\_inserter(filteredOrders),

             \[\&status](const std::shared\_ptr<Order>\& order) {

                 return order->getStatus() == status;

             });



std::accumulate для суммирования:

double total = std::accumulate(orders.begin(), orders.end(), 0.0,

    \[](double total, const std::shared\_ptr<Order>\& order) {

        return total + order->getTotalPrice();

    });



Лямбда-выражения для проверки прав:

hasPermission(const std::string\& action) const {

    static const std::vector[std::string](std::string) allowedActions = {...};

    return std::find(allowedActions.begin(), allowedActions.end(), action)

           != allowedActions.end();

}



#### **Логика ролей и прав доступа**



Возможности администратора:

* Полный доступ ко всем функциям системы
* Управление товарами (добавление, обновление, удаление)
* Просмотр всех заказов
* Изменение статусов любых заказов
* Просмотр журнала аудита
* Генерация CSV-отчетов



Возможности менеджера:

* Просмотр заказов в ожидании утверждения
* Утверждение/отклонение заказов
* Обновление количества товаров на складе
* Просмотр деталей заказов(с которыми работал)
* Изменение статусов заказов(с которыми работал)



Возможности покупателя:

* Создание новых заказов
* Добавление/удаление товаров в заказе
* Просмотр своих заказов и их статусов
* Оплата заказов (через различные методы)
* Оформление возврата заказов
* Просмотр истории статусов своих заказов



##### реализация проверки прав доступа

// Администратор (все права)

bool Admin::hasPermission(const std::string\& action) const {

    return true;

}



// Менеджер (ограниченные права)

bool Manager::hasPermission(const std::string\& action) const {

    static const std::vector[std::string](std::string) allowedActions = {

        "view\_orders", "approve\_order", "update\_stock",

        "view\_order\_details", "update\_order\_status"

    };

    return std::find(allowedActions.begin(), allowedActions.end(), action)

           != allowedActions.end();

}



#### **Аудит и история изменений**



##### таблицы аудита

order\_status\_history - отслеживает изменения статусов заказов

audit\_log - логгирует все операции



##### механизм автоматического логирования

Триггеры автоматически записывают операции:

CREATE FUNCTION log\_product() RETURNS TRIGGER AS $$

BEGIN

    INSERT INTO audit\_log (entity\_type, entity\_id, operation)

    VALUES ('product', COALESCE(NEW.product\_id, OLD.product\_id), TG\_OP);

    RETURN NEW;

END;

$$ LANGUAGE plpgsql;



CREATE TRIGGER product\_log

AFTER INSERT OR UPDATE OR DELETE ON products

FOR EACH ROW EXECUTE FUNCTION log\_product();



##### примеры записей аудита

=== Журнал аудита (последние 50 записей) ===

ID      Тип    Объект    Операция    Пользователь    Дата

---

22      product   6       insert    Администратор 2026-01-10 01:42:09

21      product   5       insert    Администратор 2026-01-09 14:48:31

20      order     999     update    Покупатель 2026-01-09 14:10:37



#### **Отчёт в формате CSV**



##### Описание отчёта «История изменений заказов и действий пользователей»

* Аудит лог - все залогированные действия
* Заказы - информация о всех заказах
* История статусов - полная история изменений статусов заказов



##### SQL-запрос через c++ для формирования отчёта

// Аудит лог

auto auditData = db->executeQuery(

    "SELECT entity\_type, entity\_id, operation, "

    "(SELECT name FROM users WHERE user\_id = al.performed\_by), "

    "performed\_at "

    "FROM audit\_log al "

    "ORDER BY performed\_at DESC"

);



// Заказы

auto ordersData = db->executeQuery(

    "SELECT o.order\_id, u.name, o.status, o.total\_price, o.order\_date "

    "FROM orders o JOIN users u ON o.user\_id = u.user\_id "

    "ORDER BY o.order\_date DESC"

);



// История статусов

auto historyData = db->executeQuery(

    "SELECT osh.order\_id, osh.old\_status, osh.new\_status, "

    "osh.changed\_at, u.name "

    "FROM order\_status\_history osh "

    "JOIN users u ON osh.changed\_by = u.user\_id "

    "ORDER BY osh.changed\_at DESC"

);



##### пример содержимого CSV-файла

=== АУДИТ ЛОГ ===

Тип объекта,ID объекта,Операция,Пользователь,Дата

order,1000,update,Менеджер,2026-01-09 02:47:53.84552

order,1000,update,Покупатель,2026-01-09 02:45:46.077039

product,2,insert,Покупатель,2026-01-09 02:45:35.16038



=== ЗАКАЗЫ ===

ID заказа,Пользователь,Статус,Сумма,Дата

1000,Покупатель,completed,30000.00,2026-01-09 02:45:46.068588

999,Покупатель,completed,100.00,2026-01-09 02:37:57.904229

1,Покупатель,completed,50000.00,2026-01-09 02:11:32.436707



=== ИСТОРИЯ СТАТУСОВ ===

ID заказа,Старый статус,Новый статус,Дата изменения,Кто изменил

1000,pending,completed,2026-01-09 02:45:46.068588,Покупатель



#### **Сборка и запуск проекта**



##### Требования к окружению

1. Компилятор C++: g++ 9.0+
2. PostgreSQL
3. libpqxx: библиотека для подключения C++ к PostgreSQL
4. CMake: версия 3.10 (пример cmakelists в проекте)



##### инструкции по сборке

использование CMakelists для сборки



##### инструкция по запуску программы

Настройка базы данных:

запустить все sql файлы в бд(чтобы запустить все функции, триггеры)



Изменение строки подключения в main.cpp:
std::string connStr = "host=localhost port=5432 dbname=online-store user=postgres password=store\_password";



Запуск программы:
./online-store



#### **пример запуска программы**



=== Интернет-магазин ===

1\. Войти как Администратор

2\. Войти как Менеджер

3\. Войти как Покупатель

4\. Выход

Выберите роль:  



#### **примеры работы меню для разных ролей**



=== Меню администратора ===

1\. Добавить новый продукт

2\. Обновить информацию о продукте

3\. Удалить продукт

4\. Просмотр всех заказов

5\. Просмотр деталей заказа

6\. Изменить статус заказа

7\. Просмотр истории статусов заказа

8\. Просмотр журнала аудита

9\. Сформировать отчёт (CSV)

10\. Выход

Выберите действие: 1

Введите название продукта: apple

Введите цену: 100

Введите количество: 3

✓ Продукт добавлен: apple (ID: 7)

✓ Действие залогировано: insert product #7



=== Меню менеджера ===

1\. Просмотр заказов в ожидании утверждения

2\. Утвердить заказ

3\. Обновить количество товара на складе

4\. Просмотр деталей заказа

5\. Изменить статус заказа

6\. Просмотр истории утверждённых заказов

7\. Просмотр истории статусов заказов

8\. Выход

Выберите действие: 2

Введите ID заказа для утверждения: 3

✓ Заказ утвержден

✓ Действие залогировано: update order #3

Действие залогировано.



=== Меню покупателя ===

1\. Создать новый заказ

2\. Добавить товар в заказ

3\. Удалить товар из заказа

4\. Просмотр моих заказов

5\. Просмотр статуса заказа

6\. Оплатить заказ

7\. Оформить возврат заказа

8\. Просмотр истории статусов заказа

9\. Выход

Выберите действие: 1

✓ Создан новый заказ #1003

✓ Действие залогировано: insert order #1003



#### **примеры логов и истории изменений заказов**



=== Журнал аудита (последние 50 записей) ===

ID      Тип    Объект     Операция  Пользователь    Дата

--------------------------------------------------------------------

25      order     1003    insert    Покупатель 2026-01-12 18:17:20

24      order     3       update    Менеджер    2026-01-12 18:16:57

23      product   7       insert    Администратор 2026-01-12 18:16:23

22      product   6       insert    Администратор 2026-01-10 01:42:09

21      product   5       insert    Администратор 2026-01-09 14:48:31



=== История статусов заказа ID: 1002 ===

Старый статус Новый статус Дата изменения Изменил (ID)

---------------------------------------------------------------------------

pending        completed      2026-01-09 03:04:19 Покупатель



Текущий статус: completed

