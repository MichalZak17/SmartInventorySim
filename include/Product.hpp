#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <iostream>
#include <compare>     // For std::partial_ordering
#include <cmath>       // For isnan checks

/**
 * @brief Abstract base class representing a product.
 *
 * The Product class encapsulates common attributes and behaviors for all products,
 * including a name, price, quantity, a unique product ID, and a shared global ID counter
 * for generating unique IDs. Being an abstract class, it includes at least one pure
 * virtual function to enforce implementation of specific product details in derived classes.
 *
 * @note The class provides public getters to retrieve individual attributes and member
 * functions to update the price and quantity of a product.
 *
 * @details
 * - Protected Members:
 *   - std::string name_: The name of the product.
 *   - double price_: The price of the product.
 *   - int quantity_: The quantity available for the product.
 *   - static int globalIdCounter_: A static counter shared among all instances for unique ID generation.
 *   - int productId_: A unique identifier assigned to each product.
 *
 * - Public Member Functions:
 *   - Product(const std::string& name, double price, int quantity): Constructor that initializes
 *     the product with a given name, price, and quantity, and assigns a unique product ID.
 *   - virtual ~Product() = default: Virtual destructor for proper cleanup in derived classes.
 *   - virtual void printInfo() const = 0: Pure virtual function to print product-specific information,
 *     making Product an abstract class.
 *   - Getters for name, price, quantity, and product ID.
 *   - void setPrice(double newPrice): Updates the price of the product.
 *   - void updateQuantity(int delta): Adjusts the product quantity by a specified delta.
 *   - std::partial_ordering operator<=>(const Product& other) const: Three-way comparison operator for comparing
 *     products based on their attributes, accounting for potential NaN values in doubles.
 *   - friend std::ostream& operator<<(std::ostream& os, const Product& prod): Friend function to support
 *     output streaming of product information.
 *
 * - Nested Class:
 *   - class Details:
 *     - @brief A helper class to encapsulate additional detailed information about a product.
 *     - Contains a single member variable, std::string additionalInfo, to store extra details.
 *     - Explicit constructor Details(const std::string& info) used for initialization.
 */
class Product {
protected:
    std::string name_;
    double price_;
    int quantity_;

    // A static attribute (shared by all products)
    static int globalIdCounter_;

    // Every product gets a unique ID
    int productId_;

public:
    // Abstraktna klasa (co najmniej 1 metoda = 0)
    Product(const std::string& name, double price, int quantity);
    virtual ~Product() = default;

    // Pure virtual -> makes Product abstract
    virtual void printInfo() const = 0;

    // Getters
    const std::string& getName()        const { return name_; }
    const std::string  getType()        const { return "Product"; }
    double             getPrice()       const { return price_; }
    int                getQuantity()    const { return quantity_; }
    int                getId()          const { return productId_; }

    // Update price and quantity
    void setPrice(double newPrice);
    void updateQuantity(int delta);

    // Operator<=>
    // Because doubles can be NaN, we use partial_ordering
    std::partial_ordering operator<=>(const Product& other) const;

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Product& prod);

    // Input operator
    friend std::istream &operator>>(std::istream &is, Product &prod);

    // Nested class
    class Details {
    public:
        std::string additionalInfo;
        explicit Details(const std::string& info)
            : additionalInfo(info) {}
    };
};

#endif
