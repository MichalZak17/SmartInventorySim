#include "Food.hpp"
#include <iostream>

Food::Food(const std::string& name, double price, int quantity,
           double weight, const std::string& expirationDate)
    : TangibleProduct(name, price, quantity, weight),
      expirationDate_(expirationDate)
{}

void Food::printInfo() const {
    std::cout << "Food: " << *this
              << " | Expires: " << expirationDate_ << "\n";
}
