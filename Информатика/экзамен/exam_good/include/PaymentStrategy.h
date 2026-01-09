#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

#include <string>  // ДОБАВЬТЕ ЭТУ СТРОКУ

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool pay(double amount) = 0;
    virtual std::string getName() const = 0;
};

#endif // PAYMENTSTRATEGY_H