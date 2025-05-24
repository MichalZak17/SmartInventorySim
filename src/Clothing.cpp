#include "Clothing.hpp"
#include <iostream>
#include <iomanip> // For std::quoted (used in operator>>)

/**
 * @brief Constructor for the Clothing class.
 * * @param name The name of the clothing item.
 * @param price The price of the clothing item.
 * @param quantity The quantity of the clothing item in inventory.
 * @param weight The weight of the clothing item.
 * @param size The size of the clothing item (e.g., "S", "M", "L", "XL").
 */
Clothing::Clothing(const std::string& name, double price, int quantity,
                   double weight, const std::string& size)
    : TangibleProduct(name, price, quantity, weight),
      size_(size)
{}

/**
 * @brief Prints information about the clothing item.
 * * This method overrides the printInfo method in TangibleProduct to
 * display specific information about the clothing item, including
 * its size.
 */
void Clothing::printInfo() const {
  // Product::operator<< handles basic info (ID, name, price, qty)
  // TangibleProduct::printInfo could call Product::printInfo and add weight,
  // or Clothing::printInfo calls its base and adds size.
  // Current Product::operator<< prints everything for Product.
  std::cout << "Clothing: " << static_cast<const Product &>(*this) // Display base Product info via its operator<<
            << " | Weight: " << getWeight() << " kg"               // Explicitly add weight
            << " | Size: " << size_ << "\n";                       // Add size
}

/**
 * @brief Input stream operator for the Clothing class.
 *
 * This operator reads the name, price, quantity, weight, and size
 * of a clothing item from the input stream. String attributes (name from Product, size from Clothing)
 * are expected to be read using std::quoted if they contain spaces.
 *
 * @param is The input stream to read from.
 * @param c The Clothing object to write to.
 * @return The input stream after reading.
 */
std::istream &operator>>(std::istream &is, Clothing &c)
{
  is >> static_cast<TangibleProduct &>(c); // Reads Product (name, price, qty using std::quoted for name) and TangibleProduct (weight)
  is >> std::quoted(c.size_);              // Read size, using std::quoted for robustness
  return is;
}