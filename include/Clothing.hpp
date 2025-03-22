#ifndef CLOTHING_HPP
#define CLOTHING_HPP

#include "TangibleProduct.hpp"
#include <string>

/**
 * @brief Clothing class representing wearable products in inventory
 * 
 * The Clothing class extends TangibleProduct to specifically represent
 * clothing items with additional size information.
 * 
 * @inherit TangibleProduct
 */
class Clothing : public TangibleProduct {
    std::string size_; // e.g. "L", "XL"

public:
    /**
     * @brief Constructor for the Clothing class.
     * 
     * @param name The name of the clothing item.
     * @param price The price of the clothing item.
     * @param quantity The quantity of the clothing item in inventory.
     * @param weight The weight of the clothing item.
     * @param size The size of the clothing item (e.g., "S", "M", "L", "XL").
     */
    Clothing(const std::string& name, double price, int quantity,
             double weight, const std::string& size);

    void printInfo() const override;
};

#endif
