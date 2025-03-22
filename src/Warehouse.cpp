#include "Warehouse.hpp"
#include <algorithm>  // Only sort, find_if
#include <iostream>

/**
 * @brief Adds a product to the warehouse.
 *
 * This method takes ownership of a Product represented by a std::unique_ptr and stores it
 * in the warehouse. The use of std::unique_ptr ensures proper memory management by transferring
 * ownership to the products_ container.
 *
 * @param product A unique pointer to the Product to be added.
 */
void Warehouse::addProduct(std::unique_ptr<Product> product) {
    products_.push_back(std::move(product));
}

/**
 * @brief Finds a product in the warehouse by its name.
 * 
 * This method searches the warehouse inventory for a product with the specified name.
 * Each call to this method increments an internal access counter.
 * 
 * @param name The name of the product to find.
 * @return std::optional<const Product*> An optional containing a pointer to the found product,
 *         or std::nullopt if no product with the given name exists in the warehouse.
 * 
 * @note This is a const method that modifies the mutable accessCount_ member variable.
 */
std::optional<const Product*> Warehouse::findProductByName(const std::string& name) const {
    ++accessCount_; // mutable variable can be changed in const method
    auto it = std::find_if(products_.begin(), products_.end(),
        [&](const std::unique_ptr<Product>& p) {
            return p->getName() == name;
        }
    );
    if (it != products_.end()) {
        return it->get();
    }
    return std::nullopt;
}

/**
 * @brief Searches for a product with the specified ID in the warehouse.
 * 
 * This method iterates through the products in the warehouse and returns
 * a pointer to the product if found. The returned pointer points to the
 * product owned by the warehouse and should not be deleted by the caller.
 *
 * @param id The ID of the product to find.
 * @return std::optional<const Product*> A pointer to the product if found,
 *         or std::nullopt if no product with the given ID exists.
 */
std::optional<const Product*> Warehouse::findProductById(int id) const {
    auto it = std::find_if(products_.begin(), products_.end(),
        [&](const std::unique_ptr<Product>& p) {
            return p->getId() == id;
        }
    );
    if (it != products_.end()) {
        return it->get();
    }
    return std::nullopt;
}

/**
 * @brief Prints information about all products in the given vector.
 * 
 * This method iterates through each product in the provided vector and calls
 * the printInfo() method on each product to display its information.
 * 
 * @param productVec A vector of unique pointers to Product objects whose information will be printed
 */
void Warehouse::printProductsInfo(const std::vector<std::unique_ptr<Product>>& productVec) const {
    for (auto& p : productVec) {
        p->printInfo();
    }
}

/**
 * @brief Sorts the products in the warehouse by price in ascending order.
 * 
 * This method uses std::sort with a lambda comparator to sort all products
 * based on their prices, from lowest to highest. After this operation,
 * products with lower prices will appear before products with higher prices
 * in the internal product collection.
 * 
 * @note This operation modifies the order of products in the warehouse.
 * @see getPrice() in Product class
 */
void Warehouse::sortByPriceAscending() {
    std::sort(products_.begin(), products_.end(),
        [](const std::unique_ptr<Product>& a, const std::unique_ptr<Product>& b) {
            // Use our operator<=> indirectly or just compare
            return (a->getPrice() < b->getPrice());
        }
    );
}

// Operator() - e.g. "periodic" update
/**
 * @brief Operator() overload for the Warehouse class, used to execute periodic operations on products.
 * 
 * This method iterates through all products stored in the warehouse and updates their prices.
 * Currently, it implements a simple pricing strategy where each product's price is reduced by 1%
 * in each execution cycle.
 * 
 * Usage example:
 *     Warehouse warehouse;
 *     warehouse(); // Executes the operator() method, updating all product prices
 */
void Warehouse::operator()() {
    for (auto& p : products_) {
        // Example: reduce price by 1% each cycle
        double newPrice = p->getPrice() * 0.99;
        p->setPrice(newPrice);
    }
}
