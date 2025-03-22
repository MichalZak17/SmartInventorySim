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
