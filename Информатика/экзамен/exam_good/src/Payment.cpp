#include "../include/Payment.h"
#include <iostream>

Payment::Payment(int paymentId, int orderId, double amount, 
                 std::unique_ptr<PaymentStrategy> strategy)
    : paymentId(paymentId), orderId(orderId), amount(amount),
      paymentDate("2024-01-01"), status("pending"), 
      paymentStrategy(std::move(strategy)) {}

bool Payment::process() {
    if (paymentStrategy) {
        if (paymentStrategy->pay(amount)) {
            status = "completed";
            return true;
        }
    }
    status = "failed";
    return false;
}

bool Payment::refund() {
    std::cout << "Возврат платежа " << paymentId << " на сумму " << amount << std::endl;
    status = "refunded";
    return true;
}

std::string Payment::getPaymentMethod() const {
    return paymentStrategy ? paymentStrategy->getName() : "Неизвестно";
}