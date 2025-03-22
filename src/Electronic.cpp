#include "Electronic.hpp"
#include <iostream>

/**
 * @brief Constructor for the Electronic class.
 * 
 * @param name The name of the electronic item.
 * @param price The price of the electronic item.
 * @param quantity The quantity of the electronic item in inventory.
 * @param weight The weight of the electronic item.
 * @param warranty The warranty period of the electronic item (e.g., "2 years").
 */
Electronic::Electronic(const std::string& name, double price, int quantity,
                       double weight, const std::string& warranty)
    : TangibleProduct(name, price, quantity, weight),
      warranty_(warranty)
{}

/**
 * @brief Prints information about the electronic item.
 * 
 * This method overrides the printInfo method in TangibleProduct to
 * display specific information about the electronic item, including
 * its warranty period.
 */
void Electronic::printInfo() const {
    std::cout << "Electronic: " << *this
              << " | Warranty: " << warranty_ << "\n";
}
