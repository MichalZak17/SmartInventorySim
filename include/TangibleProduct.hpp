#ifndef TANGIBLEPRODUCT_HPP
#define TANGIBLEPRODUCT_HPP

#include "Product.hpp"

/**
 * @brief TangibleProduct class representing physical products in inventory
 * 
 * The TangibleProduct class extends Product to specifically represent
 * physical items with additional weight information.
 * 
 * @inherit Product
 */
class TangibleProduct : public Product {
protected:
    /**
     * @brief Weight of the tangible product
     * 
     * The weight of the tangible product, e.g., in kilograms.
     */
    double weight_;  // e.g. weight in kg

public:
    /**
     * @brief Constructor for the TangibleProduct class.
     * 
     * @param name The name of the tangible product.
     * @param price The price of the tangible product.
     * @param quantity The quantity of the tangible product in inventory.
     * @param weight The weight of the tangible product.
     */
    TangibleProduct(const std::string& name, double price, int quantity, double weight);

    /**
     * @brief Destructor for the TangibleProduct class.
     */
    virtual ~TangibleProduct();

    /**
     * @brief Copy constructor for the TangibleProduct class.
     * 
     * @param other The TangibleProduct object to copy from.
     */
    TangibleProduct(const TangibleProduct& other);

    /**
     * @brief Move constructor for the TangibleProduct class.
     * 
     * @param other The TangibleProduct object to move from.
     */
    TangibleProduct(TangibleProduct&& other) noexcept;

    /**
     * @brief Copy assignment operator for the TangibleProduct class.
     * 
     * @param other The TangibleProduct object to copy from.
     * @return A reference to the assigned TangibleProduct object.
     */
    TangibleProduct& operator=(const TangibleProduct& other);

    /**
     * @brief Move assignment operator for the TangibleProduct class.
     * 
     * @param other The TangibleProduct object to move from.
     * @return A reference to the assigned TangibleProduct object.
     */
    TangibleProduct& operator=(TangibleProduct&& other) noexcept;

    /**
     * @brief Prints information about the tangible product.
     * 
     * This method overrides the printInfo method in Product to
     * display specific information about the tangible product,
     * including its weight.
     */
    virtual void printInfo() const override;

    /**
     * @brief Gets the weight of the tangible product.
     * 
     * @return The weight of the tangible product.
     */
    double getWeight() const { return weight_; }
};

#endif
