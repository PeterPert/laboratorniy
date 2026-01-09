#include "../include/SBPPayment.h"
#include <iostream>

SBPPayment::SBPPayment(const std::string& bankName, 
                       const std::string& phoneNumber)
    : bankName(bankName), phoneNumber(phoneNumber) {}

bool SBPPayment::pay(double amount) {
    std::cout << "Оплата через СБП: " << amount << " руб." << std::endl;
    std::cout << "Банк: " << bankName << std::endl;
    return true;
}

std::string SBPPayment::getName() const {
    return "СБП";
}