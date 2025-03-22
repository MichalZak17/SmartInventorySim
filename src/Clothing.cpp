#include "Clothing.hpp"
#include <iostream>

Clothing::Clothing(const std::string& name, double price, int quantity,
                   double weight, const std::string& size)
    : TangibleProduct(name, price, quantity, weight),
      size_(size)
{}

void Clothing::printInfo() const {
    std::cout << "Clothing: " << *this
              << " | Size: " << size_ << "\n";
}
