#include "../include/Product.h"

Product::Product(int id, const std::string& name, double price, 
                 int stockQuantity, const std::string& description)
    : productId(id), name(name), price(price), 
      stockQuantity(stockQuantity), description(description) {}