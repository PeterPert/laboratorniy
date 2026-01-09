cmake_minimum_required(VERSION 3.10)
project(OnlineStore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим libpqxx
find_package(libpqxx REQUIRED)

# Включаем директории
include_directories(${CMAKE_SOURCE_DIR}/include)

# Файлы исходного кода
set(SOURCES
    src/main.cpp
    src/DatabaseConnection.cpp
    src/User.cpp
    src/Admin.cpp
    src/Manager.cpp
    src/Customer.cpp
    src/Order.cpp
    src/OrderItem.cpp
    src/Product.cpp
    src/Payment.cpp
    src/PaymentStrategy.cpp
    src/BankCardPayment.cpp
    src/DigitalWalletPayment.cpp
    src/SBPPayment.cpp
    src/Logger.cpp
    src/Utils.cpp
)

# Создаем исполняемый файл
add_executable(OnlineStore ${SOURCES})

# Связываем с libpqxx
target_link_libraries(OnlineStore PRIVATE pqxx pq)