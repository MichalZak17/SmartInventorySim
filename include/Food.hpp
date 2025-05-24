#ifndef FOOD_HPP
#define FOOD_HPP

#include "TangibleProduct.hpp"
#include <string>
#include <iostream> // Required for std::istream

/**
 * @brief Food class representing food products in inventory
 * * The Food class extends TangibleProduct to specifically represent
 * food items with additional expiration date information.
 * * @inherit TangibleProduct
 */
class Food : public TangibleProduct {
    std::string expirationDate_; // e.g. "2025-12-31"

public:
    /**
     * @brief Constructor for the Food class.
     * * @param name The name of the food item.
     * @param price The price of the food item.
     * @param quantity The quantity of the food item in inventory.
     * @param weight The weight of the food item.
     * @param expirationDate The expiration date of the food item (e.g., "2025-12-31").
     */
    Food(const std::string &name, double price, int quantity,
         double weight, const std::string &expirationDate);
    /**
     * @brief Prints information about the food item.
     * * This method overrides the printInfo method in TangibleProduct to
     * display specific information about the food item, including
     * its expiration date.
     */
    void printInfo() const override;

    /**
     * @brief Gets the expiration date of the food item.
     * @return const std::string& The expiration date.
     */
    const std::string &getExpirationDate() const { return expirationDate_; }

    /**
     * @brief Input stream operator for the Food class.
     *
     * This operator reads the name, price, quantity, weight, and expiration date
     * of a food item from the input stream. String attributes (name, expirationDate)
     * are expected to be read using std::quoted if they contain spaces.
     *
     * @param is The input stream to read from.
     * @param f The Food object to write to.
     * @return The input stream after reading.
     */
    friend std::istream &operator>>(std::istream &is, Food &f);
};

#endif