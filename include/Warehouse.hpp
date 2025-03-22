#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP

#include <vector>
#include <string>
#include <memory>
#include <optional>     // We'll use optional instead of expected
#include "Product.hpp"

class Warehouse {
    // Vector of unique_ptr to store Product objects
    std::vector<std::unique_ptr<Product>> products_;

    // mutable attribute (can be changed even in const methods)
    mutable int accessCount_ = 0;

public:
    Warehouse() = default;
    ~Warehouse() = default;

    void addProduct(std::unique_ptr<Product> product);

    // find by name -> returns optional
    std::optional<const Product*> findProductByName(const std::string& name) const;

    // find by ID -> returns optional
    std::optional<const Product*> findProductById(int id) const;

    // Instead of span, we'll pass a const reference to vector
    void printProductsInfo(const std::vector<std::unique_ptr<Product>>& productVec) const;

    // Example: sort by ascending price
    void sortByPriceAscending();

    // Access to all products
    const std::vector<std::unique_ptr<Product>>& getProducts() const { return products_; }

    // Operator() to simulate e.g. periodic warehouse update
    void operator() ();
};

#endif
