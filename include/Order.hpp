#ifndef ORDER_HPP
#define ORDER_HPP

#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <vector>

class Product;

class Order {
    // Key = product ID, value = quantity
    std::map<int, int> items_;

public:
    Order() = default;

    // Add product (by ID) with a given quantity
    void addItem(const Product& product, int quantity);

    // Getters
    const std::map<int, int>& getItems() const { return items_; }

    // Calculate total price given a warehouse's product list
    double totalPrice(const std::vector<std::unique_ptr<Product>>& warehouseProducts) const;

    // Return number of unique product types in the order
    size_t itemCount() const;

    // Overload operator<< to display order details
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};

#endif
