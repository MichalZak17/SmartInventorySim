#include "TangibleProduct.hpp"
#include <utility>
#include <iostream>

/**
 * @brief Constructor for the TangibleProduct class.
 * 
 * @param name The name of the tangible product.
 * @param price The price of the tangible product.
 * @param quantity The quantity of the tangible product in inventory.
 * @param weight The weight of the tangible product.
 */
TangibleProduct::TangibleProduct(const std::string& name, double price, int quantity, double weight)
    : Product(name, price, quantity), weight_(weight)
{}

/**
 * @brief Destructor for the TangibleProduct class.
 */
TangibleProduct::~TangibleProduct() {}

/**
 * @brief Copy constructor for the TangibleProduct class.
 * 
 * @param other The TangibleProduct object to copy from.
 */
TangibleProduct::TangibleProduct(const TangibleProduct& other)
    : Product(other.name_, other.price_, other.quantity_), weight_(other.weight_)
{}

/**
 * @brief Move constructor for the TangibleProduct class.
 * 
 * @param other The TangibleProduct object to move from.
 */
TangibleProduct::TangibleProduct(TangibleProduct&& other) noexcept
    : Product(std::move(other.name_), other.price_, other.quantity_),
      weight_(other.weight_)
{
    other.price_    = 0.0;
    other.quantity_ = 0;
    other.weight_   = 0.0;
}

/**
 * @brief Copy assignment operator for the TangibleProduct class.
 * 
 * @param other The TangibleProduct object to copy from.
 * @return A reference to the assigned TangibleProduct object.
 */
TangibleProduct& TangibleProduct::operator=(const TangibleProduct& other) {
    if (this != &other) {
        name_     = other.name_;
        price_    = other.price_;
        quantity_ = other.quantity_;
        weight_   = other.weight_;
    }
    return *this;
}

/**
 * @brief Move assignment operator for the TangibleProduct class.
 * 
 * @param other The TangibleProduct object to move from.
 * @return A reference to the assigned TangibleProduct object.
 */
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

/**
 * @brief Prints information about the tangible product.
 * 
 * This method overrides the printInfo method in Product to
 * display specific information about the tangible product,
 * including its weight.
 */
void TangibleProduct::printInfo() const {
    std::cout << "TangibleProduct: " << *this
              << " | Weight: " << weight_ << " kg\n";
}
