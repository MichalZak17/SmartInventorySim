#ifndef FOOD_HPP
#define FOOD_HPP

#include "TangibleProduct.hpp"
#include <string>

/**
 * @brief Food class representing food products in inventory
 * 
 * The Food class extends TangibleProduct to specifically represent
 * food items with additional expiration date information.
 * 
 * @inherit TangibleProduct
 */
class Food : public TangibleProduct {
    std::string expirationDate_; // e.g. "2025-12-31"

public:
    /**
     * @brief Constructor for the Food class.
     * 
     * @param name The name of the food item.
     * @param price The price of the food item.
     * @param quantity The quantity of the food item in inventory.
     * @param weight The weight of the food item.
     * @param expirationDate The expiration date of the food item (e.g., "2025-12-31").
     */
    Food(const std::string& name, double price, int quantity,
         double weight, const std::string& expirationDate);

    /**
     * @brief Prints information about the food item.
     * 
     * This method overrides the printInfo method in TangibleProduct to
     * display specific information about the food item, including
     * its expiration date.
     */
    void printInfo() const override;
};

#endif
