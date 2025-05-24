#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP

#include <span> // For std::span
#include <vector>
#include <string>
#include <memory>
#include <expected>
#include <optional>
#include <algorithm> // For std::sort, std::find_if, std::for_each
#include "Product.hpp"

/**
 * @brief Warehouse class representing a storage facility for products
 * * The Warehouse class manages a collection of products and provides methods
 * to add, find, and sort products. It also keeps track of the number of times
 * products are accessed (by name).
 */
class Warehouse
{
    /**
     * @brief Vector of unique pointers to store Product objects
     * * The products_ vector holds unique pointers to Product objects, ensuring
     * that each product is owned by the warehouse and properly managed.
     */
    std::vector<std::unique_ptr<Product>> products_;

    /**
     * @brief Mutable attribute to track the number of product accesses by name
     * * The accessCount_ variable is mutable, allowing it to be modified even
     * in const methods. It keeps track of how many times products are accessed by name.
     */
    mutable int accessCount_ = 0;

public:
    Warehouse() = default;
    ~Warehouse() = default; // Default destructor is fine with unique_ptr managing memory

    // Rule of Five: If a destructor, copy constructor, copy assignment,
    // move constructor, or move assignment is declared, the others should be considered.
    // Here, unique_ptr handles resource management, so default move operations are fine.
    // Copy operations for a Warehouse would be complex (deep copy of products) and are
    // typically deleted or explicitly defined if needed. For now, we rely on defaults
    // and primarily pass Warehouse by reference. If copies were needed:
    // Warehouse(const Warehouse& other); // Would need deep copy
    // Warehouse& operator=(const Warehouse& other); // Would need deep copy
    Warehouse(Warehouse &&other) = default;
    Warehouse &operator=(Warehouse &&other) = default;

    /**
     * @brief Adds a product to the warehouse
     * * This method takes ownership of a Product represented by a unique pointer
     * and stores it in the warehouse.
     * * @param product A unique pointer to the Product to be added
     */
    void addProduct(std::unique_ptr<Product> product);
    /**
     * @brief Finds a product in the warehouse by its name
     * * This method searches the warehouse inventory for a product with the
     * specified name. Each call to this method increments the access count.
     * * @param name The name of the product to find
     * @return An optional containing a pointer to the found product (const Product*), or
     * std::nullopt if no product with the given name exists
     */
    std::optional<const Product *> findProductByName(const std::string &name) const;
    /**
     * @brief Finds a product in the warehouse by its ID
     * * This method searches the warehouse inventory for a product with the
     * specified ID.
     * * @param id The ID of the product to find
     * @return An expected containing a pointer to the found product (const Product*), or
     * an error string if no product with the given ID exists
     */
    std::expected<const Product *, std::string> findProductById(int id) const;
    /**
     * @brief Prints information about all products in the given span
     * * This method iterates through each product in the provided span and
     * calls the printInfo() method on each product to display its information.
     * * @param products_span A span of unique pointers to Product objects whose
     * information will be printed
     */
    void printProductsInfo(std::span<const std::unique_ptr<Product>> products_span) const;
    /**
     * @brief Sorts the products in the warehouse by price in ascending order
     * * This method uses std::sort with a lambda comparator to sort all products
     * based on their prices, from lowest to highest.
     */
    void sortByPriceAscending();

    /**
     * @brief Gets the products in the warehouse
     * * @return A const reference to the vector of unique pointers to Product objects
     */
    const std::vector<std::unique_ptr<Product>>& getProducts() const { return products_; }

    /**
     * @brief Operator() to simulate periodic warehouse update (e.g., price reduction)
     * * This method iterates through all products stored in the warehouse and
     * updates their prices. Currently, it implements a simple pricing strategy
     * where each product's price is reduced by 1% in each execution cycle.
     */
    void operator() ();
};

#endif