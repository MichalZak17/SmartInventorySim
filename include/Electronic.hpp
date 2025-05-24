#ifndef ELECTRONIC_HPP
#define ELECTRONIC_HPP

#include "TangibleProduct.hpp"
#include <string>
#include <iostream> // Required for std::istream

/**
 * @brief Electronic class representing electronic products in inventory
 * * The Electronic class extends TangibleProduct to specifically represent
 * electronic items with additional warranty information.
 * * @inherit TangibleProduct
 */
class Electronic : public TangibleProduct {
    std::string warranty_; // e.g. "2 years"

public:
    /**
     * @brief Constructor for the Electronic class.
     * * @param name The name of the electronic item.
     * @param price The price of the electronic item.
     * @param quantity The quantity of the electronic item in inventory.
     * @param weight The weight of the electronic item.
     * @param warranty The warranty period of the electronic item (e.g., "2 years").
     */
    Electronic(const std::string &name, double price, int quantity,
               double weight, const std::string &warranty);
    /**
     * @brief Prints information about the electronic item.
     * * This method overrides the printInfo method in TangibleProduct to
     * display specific information about the electronic item, including
     * its warranty period.
     */
    void printInfo() const override;

    /**
     * @brief Gets the warranty period of the electronic item.
     * @return const std::string& The warranty period.
     */
    const std::string &getWarranty() const { return warranty_; }

    /**
     * @brief Input stream operator for the Electronic class.
     *
     * This operator reads the name, price, quantity, weight, and warranty
     * of an electronic item from the input stream. String attributes (name, warranty)
     * are expected to be read using std::quoted if they contain spaces.
     *
     * @param is The input stream to read from.
     * @param e The Electronic object to write to.
     * @return The input stream after reading.
     */
    friend std::istream &operator>>(std::istream &is, Electronic &e);
};

#endif