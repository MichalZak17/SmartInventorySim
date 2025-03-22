#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP

#include <vector>
#include <string>
#include <memory>
#include <optional>     // We'll use optional instead of expected
#include "Product.hpp"

/**
 * @brief Warehouse class representing a storage facility for products
 * 
 * The Warehouse class manages a collection of products and provides methods
 * to add, find, and sort products. It also keeps track of the number of times
 * products are accessed.
 */
class Warehouse {
    /**
     * @brief Vector of unique pointers to store Product objects
     * 
     * The products_ vector holds unique pointers to Product objects, ensuring
     * that each product is owned by the warehouse and properly managed.
     */
    std::vector<std::unique_ptr<Product>> products_;

    /**
     * @brief Mutable attribute to track the number of product accesses
     * 
     * The accessCount_ variable is mutable, allowing it to be modified even
     * in const methods. It keeps track of how many times products are accessed.
     */
    mutable int accessCount_ = 0;

public:
    Warehouse() = default;
    ~Warehouse() = default;

    /**
     * @brief Adds a product to the warehouse
     * 
     * This method takes ownership of a Product represented by a unique pointer
     * and stores it in the warehouse.
     * 
     * @param product A unique pointer to the Product to be added
     */
    void addProduct(std::unique_ptr<Product> product);

    /**
     * @brief Finds a product in the warehouse by its name
     * 
     * This method searches the warehouse inventory for a product with the
     * specified name. Each call to this method increments the access count.
     * 
     * @param name The name of the product to find
     * @return An optional containing a pointer to the found product, or
     *         std::nullopt if no product with the given name exists
     */
    std::optional<const Product*> findProductByName(const std::string& name) const;

    /**
     * @brief Finds a product in the warehouse by its ID
     * 
     * This method searches the warehouse inventory for a product with the
     * specified ID.
     * 
     * @param id The ID of the product to find
     * @return An optional containing a pointer to the found product, or
     *         std::nullopt if no product with the given ID exists
     */
    std::optional<const Product*> findProductById(int id) const;

    /**
     * @brief Prints information about all products in the given vector
     * 
     * This method iterates through each product in the provided vector and
     * calls the printInfo() method on each product to display its information.
     * 
     * @param productVec A vector of unique pointers to Product objects whose
     *                   information will be printed
     */
    void printProductsInfo(const std::vector<std::unique_ptr<Product>>& productVec) const;

    /**
     * @brief Sorts the products in the warehouse by price in ascending order
     * 
     * This method uses std::sort with a lambda comparator to sort all products
     * based on their prices, from lowest to highest.
     */
    void sortByPriceAscending();

    /**
     * @brief Gets the products in the warehouse
     * 
     * @return A const reference to the vector of unique pointers to Product objects
     */
    const std::vector<std::unique_ptr<Product>>& getProducts() const { return products_; }

    /**
     * @brief Operator() to simulate periodic warehouse update
     * 
     * This method iterates through all products stored in the warehouse and
     * updates their prices. Currently, it implements a simple pricing strategy
     * where each product's price is reduced by 1% in each execution cycle.
     */
    void operator() ();
};

#endif
