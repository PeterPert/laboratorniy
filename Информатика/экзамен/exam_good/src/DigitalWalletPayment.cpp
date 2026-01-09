#include "../include/DigitalWalletPayment.h"
#include <iostream>

DigitalWalletPayment::DigitalWalletPayment(const std::string& walletId, 
                                           const std::string& phoneNumber)
    : walletId(walletId), phoneNumber(phoneNumber) {}

bool DigitalWalletPayment::pay(double amount) {
    std::cout << "Оплата электронным кошельком: " << amount << " руб." << std::endl;
    std::cout << "Кошелек: " << walletId << std::endl;
    return true;
}

std::string DigitalWalletPayment::getName() const {
    return "Электронный кошелек";
}