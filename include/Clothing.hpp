#ifndef CLOTHING_HPP
#define CLOTHING_HPP

#include "TangibleProduct.hpp"
#include <string>
#include <iostream> // Required for std::istream

/**
 * @brief Clothing class representing wearable products in inventory
 * * The Clothing class extends TangibleProduct to specifically represent
 * clothing items with additional size information.
 * * @inherit TangibleProduct
 */
class Clothing : public TangibleProduct {
    std::string size_; // e.g. "L", "XL"

public:
    /**
     * @brief Constructor for the Clothing class.
     * * @param name The name of the clothing item.
     * @param price The price of the clothing item.
     * @param quantity The quantity of the clothing item in inventory.
     * @param weight The weight of the clothing item.
     * @param size The size of the clothing item (e.g., "S", "M", "L", "XL").
     */
    Clothing(const std::string& name, double price, int quantity,
             double weight, const std::string& size);

    void printInfo() const override;

    /**
     * @brief Gets the size of the clothing item.
     * @return const std::string& The size of the clothing item.
     */
    const std::string &getSize() const { return size_; }

    /**
     * @brief Input stream operator for the Clothing class.
     *
     * This operator reads the name, price, quantity, weight, and size
     * of a clothing item from the input stream. String attributes (name, size)
     * are expected to be read using std::quoted if they contain spaces.
     *
     * @param is The input stream to read from.
     * @param c The Clothing object to write to.
     * @return The input stream after reading.
     */
    friend std::istream &operator>>(std::istream &is, Clothing &c);
};

#endif