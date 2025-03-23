#include "Clothing.hpp"
#include <iostream>

/**
 * @brief Constructor for the Clothing class.
 * 
 * @param name The name of the clothing item.
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
 * 
 * This method overrides the printInfo method in TangibleProduct to
 * display specific information about the clothing item, including
 * its size.
 */
void Clothing::printInfo() const {
    std::cout << "Clothing: " << *this
              << " | Size: " << size_ << "\n";
}

/**
 * @brief Input stream operator for the Clothing class.
 *
 * This operator reads the name, price, quantity, weight, and size
 * of a clothing item from the input stream.
 *
 * @param is The input stream to read from.
 * @param c The Clothing object to write to.
 * @return The input stream after reading.
 */
std::istream &operator>>(std::istream &is, Clothing &c)
{
  is >> static_cast<TangibleProduct &>(c);
  is >> c.size_;
  return is;
}