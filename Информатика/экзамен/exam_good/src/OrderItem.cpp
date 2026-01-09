#include "../include/OrderItem.h"

OrderItem::OrderItem(int id, int orderId, int productId, int quantity, 
                     double price, const std::string& productName)
    : orderItemId(id), orderId(orderId), productId(productId),
      quantity(quantity), price(price), productName(productName) {}