#ifndef SBPPAYMENT_H
#define SBPPAYMENT_H

#include "PaymentStrategy.h"
#include <string>

class SBPPayment : public PaymentStrategy {
private:
    std::string bankName;
    std::string phoneNumber;

public:
    SBPPayment(const std::string& bankName, 
               const std::string& phoneNumber);
    
    bool pay(double amount) override;
    std::string getName() const override;  // ТОЛЬКО ОБЪЯВЛЕНИЕ
};

#endif // SBPPAYMENT_H