#include "TangibleProduct.hpp"
#include <utility>
#include <iostream>

TangibleProduct::TangibleProduct(const std::string& name, double price, int quantity, double weight)
    : Product(name, price, quantity), weight_(weight)
{}

TangibleProduct::~TangibleProduct() {}

TangibleProduct::TangibleProduct(const TangibleProduct& other)
    : Product(other.name_, other.price_, other.quantity_), weight_(other.weight_)
{}

TangibleProduct::TangibleProduct(TangibleProduct&& other) noexcept
    : Product(std::move(other.name_), other.price_, other.quantity_),
      weight_(other.weight_)
{
    other.price_    = 0.0;
    other.quantity_ = 0;
    other.weight_   = 0.0;
}

TangibleProduct& TangibleProduct::operator=(const TangibleProduct& other) {
    if (this != &other) {
        name_     = other.name_;
        price_    = other.price_;
        quantity_ = other.quantity_;
        weight_   = other.weight_;
    }
    return *this;
}

TangibleProduct& TangibleProduct::operator=(TangibleProduct&& other) noexcept {
    if (this != &other) {
        name_     = std::move(other.name_);
        price_    = other.price_;
        quantity_ = other.quantity_;
        weight_   = other.weight_;

        other.price_    = 0.0;
        other.quantity_ = 0;
        other.weight_   = 0.0;
    }
    return *this;
}

void TangibleProduct::printInfo() const {
    std::cout << "TangibleProduct: " << *this
              << " | Weight: " << weight_ << " kg\n";
}
