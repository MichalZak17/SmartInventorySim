#include "Food.hpp"
#include <iostream>

/**
 * @brief Constructor for the Food class.
 * 
 * @param name The name of the food item.
 * @param price The price of the food item.
 * @param quantity The quantity of the food item in inventory.
 * @param weight The weight of the food item.
 * @param expirationDate The expiration date of the food item (e.g., "2025-12-31").
 */
Food::Food(const std::string& name, double price, int quantity,
           double weight, const std::string& expirationDate)
    : TangibleProduct(name, price, quantity, weight),
      expirationDate_(expirationDate)
{}

/**
 * @brief Prints information about the food item.
 * 
 * This method overrides the printInfo method in TangibleProduct to
 * display specific information about the food item, including
 * its expiration date.
 */
void Food::printInfo() const {
    std::cout << "Food: " << *this
              << " | Expires: " << expirationDate_ << "\n";
}

/**
 * @brief Input stream operator for the Food class.
 *
 * This operator reads the name, price, quantity, weight, and expiration date
 * of a food item from the input stream.
 *
 * @param is The input stream to read from.
 * @param f The Food object to write to.
 * @return The input stream after reading.
 */
std::istream &operator>>(std::istream &is, Food &f)
{
  is >> static_cast<TangibleProduct &>(f);
  is >> f.expirationDate_;
  return is;
}
