#include "Product.hpp"

int Product::globalIdCounter_ = 0;

Product::Product(const std::string& name, double price, int quantity)
    : name_(name), price_(price), quantity_(quantity), productId_(++globalIdCounter_)
{
}

void Product::setPrice(double newPrice) {
    price_ = newPrice;
}

void Product::updateQuantity(int delta) {
    quantity_ += delta;
}

// Because double comparisons can yield partial ordering (NaN issues),
// we manually implement partial_ordering logic:
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

std::ostream& operator<<(std::ostream& os, const Product& prod) {
    os << "[ID:" << prod.productId_ << "] "
       << prod.name_
       << " | Price: " << prod.price_
       << " | Qty: "   << prod.quantity_;
    return os;
}
