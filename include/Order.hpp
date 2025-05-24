#ifndef ORDER_HPP
#define ORDER_HPP

#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate

class Product;   // Forward declaration
class Warehouse; // Forward declaration for totalPrice

/**
 * @brief Order class representing a customer's order
 * * The Order class manages a collection of products and their quantities
 * that a customer wants to purchase. It provides methods to add items,
 * calculate the total price, and get the number of unique product types
 * in the order.
 */
class Order {
    /**
     * @brief Map storing product IDs and their quantities
     * * The key is the product ID, and the value is the quantity of that product
     * in the order.
     */
    std::map<int, int> items_;

public:
    Order() = default;
    /**
     * @brief Adds a product to the order with a given quantity
     * * If the product is already in the order, its quantity is increased by the
     * specified amount. Otherwise, the product is added to the order with the
     * given quantity.
     * * @param product The product to add to the order
     * @param quantity The quantity of the product to add
     */
    void addItem(const Product &product, int quantity);
    /**
     * @brief Gets the items in the order
     * * @return A const reference to the map of product IDs and their quantities
     */
    const std::map<int, int>& getItems() const { return items_; }

    /**
     * @brief Calculates the total price of the order
     * * This method calculates the total price of all items in the order based on
     * the prices of the products in the provided warehouse.
     * * @param warehouse The Warehouse object to find product prices.
     * @return The total price of the order
     */
    double totalPrice(const Warehouse &warehouse) const; // Changed parameter
    /**
     * @brief Gets the number of unique product types in the order
     * * @return The number of unique product types in the order
     */
    size_t itemCount() const;
    /**
     * @brief Overloads the stream insertion operator to display order details
     * * This method allows the order details to be printed to an output stream.
     * * @param os The output stream
     * @param order The order to display
     * @return A reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Order &order);
    /**
     * @brief Overloads the stream extraction operator to read order details
     *
     * This method allows order details to be read from an input stream.
     * It expects the number of items, followed by pairs of product_id and quantity.
     *
     * @param is The input stream
     * @param order The order to populate
     * @return A reference to the input stream
     */
    friend std::istream &operator>>(std::istream &is, Order &order);
    /**
     * @brief Removes an item from the order
     *
     * This method removes an item from the order with the specified product ID.
     *
     * @param productId The ID of the product to remove
     */
    void removeItem(int productId);
    /**
     * @brief Edits the quantity of an item in the order
     *
     * This method changes the quantity of an item in the order with the specified
     * product ID to the new quantity. If newQuantity is 0 or less, the item is removed.
     *
     * @param productId The ID of the product to edit
     * @param newQuantity The new quantity of the product
     */
    void editItemQuantity(int productId, int newQuantity);
};

#endif