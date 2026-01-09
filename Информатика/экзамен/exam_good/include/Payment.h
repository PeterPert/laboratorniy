#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <memory>
#include "PaymentStrategy.h"

class Payment {
private:
    int paymentId;
    int orderId;
    double amount;
    std::string paymentDate;
    std::string status;
    std::unique_ptr<PaymentStrategy> paymentStrategy;

public:
    Payment(int paymentId, int orderId, double amount, 
            std::unique_ptr<PaymentStrategy> strategy);
    ~Payment() = default;
    
    bool process();
    bool refund();
    
    // Геттеры
    int getPaymentId() const { return paymentId; }
    int getOrderId() const { return orderId; }
    double getAmount() const { return amount; }
    std::string getPaymentDate() const { return paymentDate; }
    std::string getStatus() const { return status; }
    std::string getPaymentMethod() const;
};

#endif // PAYMENT_H