#ifndef BANKCARDPAYMENT_H
#define BANKCARDPAYMENT_H

#include "PaymentStrategy.h"
#include <string>

class BankCardPayment : public PaymentStrategy {
private:
    std::string cardNumber;
    std::string expiryDate;
    std::string cvv;

public:
    BankCardPayment(const std::string& cardNumber, 
                    const std::string& expiryDate, 
                    const std::string& cvv);
    
    bool pay(double amount) override;
    std::string getName() const override;  // ТОЛЬКО ОБЪЯВЛЕНИЕ
};

#endif // BANKCARDPAYMENT_H