#include "../include/BankCardPayment.h"
#include <iostream>

BankCardPayment::BankCardPayment(const std::string& cardNumber, 
                                 const std::string& expiryDate, 
                                 const std::string& cvv)
    : cardNumber(cardNumber), expiryDate(expiryDate), cvv(cvv) {}

bool BankCardPayment::pay(double amount) {
    std::cout << "Оплата банковской картой: " << amount << " руб." << std::endl;
    std::cout << "Карта: **** **** **** " << cardNumber.substr(cardNumber.length() - 4) << std::endl;
    // Здесь должна быть реальная логика оплаты
    return true;
}

// Эта функция теперь реализована
std::string BankCardPayment::getName() const {
    return "Банковская карта";
}