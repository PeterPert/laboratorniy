#ifndef DIGITALWALLETPAYMENT_H
#define DIGITALWALLETPAYMENT_H

#include "PaymentStrategy.h"
#include <string>

class DigitalWalletPayment : public PaymentStrategy {
private:
    std::string walletId;
    std::string phoneNumber;

public:
    DigitalWalletPayment(const std::string& walletId, 
                         const std::string& phoneNumber);
    
    bool pay(double amount) override;
    std::string getName() const override;  // ТОЛЬКО ОБЪЯВЛЕНИЕ
};

#endif // DIGITALWALLETPAYMENT_H