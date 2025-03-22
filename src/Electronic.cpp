#include "Electronic.hpp"
#include <iostream>

Electronic::Electronic(const std::string& name, double price, int quantity,
                       double weight, const std::string& warranty)
    : TangibleProduct(name, price, quantity, weight),
      warranty_(warranty)
{}

void Electronic::printInfo() const {
    std::cout << "Electronic: " << *this
              << " | Warranty: " << warranty_ << "\n";
}
