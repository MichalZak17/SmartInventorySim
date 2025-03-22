#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP

#include <vector>
#include "Order.hpp"

/**
 * @brief Manages a collection of orders and provides functionality to create and process them.
 * 
 * The OrderManager class is responsible for maintaining a list of orders and provides
 * methods to create new orders and process existing ones. It serves as a central 
 * management point for all orders in the inventory system.
 */
class OrderManager {
    std::vector<Order> orders_;

public:
    OrderManager() = default;

    void createOrder(const Order& order);
    void processAllOrders();

    const std::vector<Order>& getOrders() const { return orders_; }
};

#endif
