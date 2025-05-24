#include "TangibleProduct.hpp"
#include <utility> // For std::move
#include <iostream>

/**
 * @brief Constructor for the TangibleProduct class.
 * * @param name The name of the tangible product.
 * @param price The price of the tangible product.
 * @param quantity The quantity of the tangible product in inventory.
 * @param weight The weight of the tangible product.
 */
TangibleProduct::TangibleProduct(const std::string& name, double price, int quantity, double weight)
    : Product(name, price, quantity), weight_(weight)
{
    if (weight_ < 0)
    {
        std::cerr << "Warning: TangibleProduct '" << name << "' created with negative weight. Setting to 0." << std::endl;
        weight_ = 0.0;
    }
}

/**
 * @brief Destructor for the TangibleProduct class.
 */
TangibleProduct::~TangibleProduct() {} // Default implementation is fine.

/**
 * @brief Copy constructor for the TangibleProduct class.
 * * Creates a new TangibleProduct as a copy of 'other'.
 * The new product will get a new unique ID via the Product base class constructor.
 * * @param other The TangibleProduct object to copy from.
 */
TangibleProduct::TangibleProduct(const TangibleProduct &other)
    : Product(other.name_, other.price_, other.quantity_), // Calls Product constructor, gets new ID
      weight_(other.weight_)
{
    // productId_ is handled by Product constructor
}

/**
 * @brief Move constructor for the TangibleProduct class.
 * * Moves the resources from 'other' to this new TangibleProduct.
 * 'other' is left in a valid but unspecified state.
 * The new product will get a new unique ID via the Product base class constructor,
 * as product identity (ID) is generally not moved with contents.
 * * @param other The TangibleProduct object to move from.
 */
TangibleProduct::TangibleProduct(TangibleProduct &&other) noexcept
    : Product(std::move(other.name_), other.price_, other.quantity_), // name_ is moved, price/qty copied, new ID from Product ctor
      weight_(other.weight_)
{
    // Reset other's members that were copied or might hold significant value
    // other.name_ is already moved from.
    other.price_    = 0.0;
    other.quantity_ = 0;
    other.weight_   = 0.0;
    // other.productId_ remains, but this new object has a different productId_.
}

/**
 * @brief Copy assignment operator for the TangibleProduct class.
 * * Assigns the content of 'other' to this TangibleProduct.
 * The productId_ of 'this' object remains unchanged.
 * * @param other The TangibleProduct object to copy from.
 * @return A reference to the assigned TangibleProduct object (*this).
 */
TangibleProduct& TangibleProduct::operator=(const TangibleProduct& other) {
    if (this != &other) {
        // Call base class assignment operator if it exists and makes sense
        // Product::operator=(other); // If Product had one.
        // For now, assign Product members directly (except productId_).
        name_     = other.name_;
        price_    = other.price_;
        quantity_ = other.quantity_;
        // productId_ is not changed by assignment of content.

        weight_ = other.weight_; // Assign TangibleProduct specific members
    }
    return *this;
}

/**
 * @brief Move assignment operator for the TangibleProduct class.
 * * Moves the resources from 'other' to this TangibleProduct.
 * The productId_ of 'this' object remains unchanged.
 * 'other' is left in a valid but unspecified state.
 * * @param other The TangibleProduct object to move from.
 * @return A reference to the assigned TangibleProduct object (*this).
 */
TangibleProduct& TangibleProduct::operator=(TangibleProduct&& other) noexcept {
    if (this != &other) {
        // Product::operator=(std::move(other)); // If Product had one
        name_     = std::move(other.name_);
        price_    = other.price_;
        quantity_ = other.quantity_;
        // productId_ is not changed by assignment of content.

        weight_ = other.weight_; // Assign TangibleProduct specific members

        // Reset other's members
        // other.name_ is already moved from.
        other.price_    = 0.0;
        other.quantity_ = 0;
        other.weight_   = 0.0;
    }
    return *this;
}

/**
 * @brief Prints information about the tangible product.
 * * This method is overridden by derived classes like Electronic, Clothing, Food.
 * If called directly on a TangibleProduct instance (not typical as Product is abstract
 * and Warehouse stores Product pointers), it would display base product info and weight.
 */
void TangibleProduct::printInfo() const {
    // This implementation might be shadowed by derived classes if they don't call TangibleProduct::printInfo().
    // Typically, derived classes (Electronic, etc.) will provide their own complete printInfo.
    std::cout << "TangibleProduct: " << static_cast<const Product &>(*this) // Display base Product info
              << " | Weight: " << weight_ << " kg\n";
}

/**
 * @brief Overloaded input stream operator for TangibleProduct class
 *
 * Reads Product base class data (name, price, quantity via Product::operator>>)
 * and then reads the weight_ member variable for TangibleProduct.
 * Name is read using std::quoted by Product::operator>>.
 *
 * @param is The input stream to read from
 * @param tp The TangibleProduct object to fill with data
 * @return std::istream& Reference to the input stream
 */
std::istream &operator>>(std::istream &is, TangibleProduct &tp)
{
    is >> static_cast<Product &>(tp); // This will use Product::operator>> for name, price, quantity
    is >> tp.weight_;

    if (tp.weight_ < 0 && is.good())
    {
        // std::cerr << "Warning: Read negative weight for tangible product. Setting to 0." << std::endl; // Could be noisy
        tp.weight_ = 0.0;
    }
    return is;
}