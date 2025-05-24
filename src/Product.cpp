#include "Product.hpp"
#include <iomanip> // For std::quoted (used in operator>>)
#include <cmath>   // For std::isnan

// Initialize static member
int Product::globalIdCounter_ = 0;

/**
 * @brief Constructor for the Product class.
 * * @param name The name of the product.
 * @param price The price of the product.
 * @param quantity The quantity of the product in inventory.
 */
Product::Product(const std::string& name, double price, int quantity)
    : name_(name), price_(price), quantity_(quantity), productId_(++globalIdCounter_)
{
    // Basic validation, can be expanded
    if (price < 0)
    {
        // Consider throwing an exception or setting a default valid price
        std::cerr << "Warning: Product '" << name << "' created with negative price. Setting to 0." << std::endl;
        price_ = 0.0;
    }
    if (quantity < 0)
    {
        // Consider throwing an exception or setting a default valid quantity
        std::cerr << "Warning: Product '" << name << "' created with negative quantity. Setting to 0." << std::endl;
        quantity_ = 0;
    }
}

/**
 * @brief Sets the price of the product.
 * * @param newPrice The new price of the product. If negative, price is set to 0.
 */
void Product::setPrice(double newPrice) {
    if (newPrice < 0)
    {
        std::cerr << "Warning: Attempted to set negative price for product ID " << productId_
                  << ". Setting price to 0." << std::endl;
        price_ = 0.0;
    }
    else
    {
        price_ = newPrice;
    }
}

/**
 * @brief Updates the quantity of the product.
 * * @param delta The change in quantity (can be positive or negative).
 * If the update results in a negative quantity, the quantity is set to 0.
 */
void Product::updateQuantity(int delta) {
    if (quantity_ + delta < 0)
    {
        std::cerr << "Warning: Update would result in negative quantity for product ID " << productId_
                  << ". Setting quantity to 0." << std::endl;
        quantity_ = 0;
    }
    else
    {
        quantity_ += delta;
    }
}

/**
 * @brief Three-way comparison operator for Product.
 * * This operator compares two products based on their price (ascending) and then by name (ascending lexicographically).
 * It handles NaN values in the price by returning std::partial_ordering::unordered if either price is NaN.
 * * @param other The other product to compare with.
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
    int name_cmp = name_.compare(other.name_);
    if (name_cmp < 0)
    {
        return std::partial_ordering::less;
    }
    if (name_cmp > 0)
    {
        return std::partial_ordering::greater;
    }
    // If prices and names are the same, compare by ID to ensure a consistent ordering if needed,
    // though for equivalence, this part might not be strictly necessary for std::partial_ordering::equivalent.
    // However, if used in contexts expecting strict weak ordering, ID comparison helps.
    if (productId_ < other.productId_)
    {
        return std::partial_ordering::less;
    }
    if (productId_ > other.productId_)
    {
        return std::partial_ordering::greater;
    }
    return std::partial_ordering::equivalent;
}

/**
 * @brief Overloaded stream insertion operator for Product (for display).
 * * This operator allows the product details (ID, name, price, quantity) to be printed to an output stream.
 * This is primarily intended for display purposes.
 * * @param os The output stream.
 * @param prod The product to display.
 * @return std::ostream& A reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const Product& prod) {
    // Note: This operator<< is for display.
    // For file I/O that needs to be parsed by operator>>, save attributes manually.
    os << "[ID:" << prod.productId_ << "] "
       << prod.name_                                                        // Name displayed as is, std::quoted not typically used for console display here
       << " | Price: " << std::fixed << std::setprecision(2) << prod.price_ // Format price
       << " | Qty: " << prod.quantity_;
    return os;
}

/**
 * @brief Input stream operator overload for Product class (for file/user input).
 *
 * Reads the name (using std::quoted to handle spaces), price, and quantity
 * properties of a Product from an input stream.
 * This operator is used when reading Product data from files or standard input.
 * Since Product is an abstract class, this operator will be used through derived classes
 * that are cast to Product.
 *
 * @param is The input stream to read from
 * @param prod The Product object to populate
 * @return std::istream& Reference to the input stream after reading
 */
std::istream &operator>>(std::istream &is, Product &prod)
{
    // Reads name (quoted), price, quantity.
    // Derived classes will call this and then read their own members.
    is >> std::quoted(prod.name_) >> prod.price_ >> prod.quantity_;

    // Basic validation after read
    if (prod.price_ < 0 && is.good())
    { // Check is.good() in case read itself failed
        // std::cerr << "Warning: Read negative price for product. Setting to 0." << std::endl; // Could be noisy
        prod.price_ = 0.0;
    }
    if (prod.quantity_ < 0 && is.good())
    {
        // std::cerr << "Warning: Read negative quantity for product. Setting to 0." << std::endl; // Could be noisy
        prod.quantity_ = 0;
    }
    return is;
}