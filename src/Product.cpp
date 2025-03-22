#include "Product.hpp"

int Product::globalIdCounter_ = 0;

/**
 * @brief Constructor for the Product class.
 * 
 * @param name The name of the product.
 * @param price The price of the product.
 * @param quantity The quantity of the product in inventory.
 */
Product::Product(const std::string& name, double price, int quantity)
    : name_(name), price_(price), quantity_(quantity), productId_(++globalIdCounter_)
{
}

/**
 * @brief Sets the price of the product.
 * 
 * @param newPrice The new price of the product.
 */
void Product::setPrice(double newPrice) {
    price_ = newPrice;
}

/**
 * @brief Updates the quantity of the product.
 * 
 * @param delta The change in quantity (positive or negative).
 */
void Product::updateQuantity(int delta) {
    quantity_ += delta;
}

/**
 * @brief Three-way comparison operator for Product.
 * 
 * This operator compares two products based on their price and name.
 * It handles NaN values in the price by returning unordered if either
 * price is NaN.
 * 
 * @param other The other product to compare with.
 * @return std::partial_ordering The result of the comparison.
 */
std::partial_ordering Product::operator<=>(const Product& other) const {
    // Compare price first
    if (std::isnan(price_) || std::isnan(other.price_)) {
        return std::partial_ordering::unordered;
    }
    if (price_ < other.price_) {
        return std::partial_ordering::less;
    }
    if (price_ > other.price_) {
        return std::partial_ordering::greater;
    }
    // If price is effectively the same, compare by name
    int cmp = name_.compare(other.name_);
    if (cmp < 0) {
        return std::partial_ordering::less;
    }
    else if (cmp > 0) {
        return std::partial_ordering::greater;
    }
    else {
        return std::partial_ordering::equivalent;
    }
}

/**
 * @brief Overloaded stream insertion operator for Product.
 * 
 * This operator allows the product details to be printed to an output stream.
 * 
 * @param os The output stream.
 * @param prod The product to display.
 * @return std::ostream& A reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const Product& prod) {
    os << "[ID:" << prod.productId_ << "] "
       << prod.name_
       << " | Price: " << prod.price_
       << " | Qty: "   << prod.quantity_;
    return os;
}
