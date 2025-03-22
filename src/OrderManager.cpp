#include "OrderManager.hpp"
#include <algorithm>
#include <iostream>

/**
 * @brief Adds a new order to the order manager.
 * 
 * This method appends the specified order to the internal orders collection.
 * 
 * @param order The Order object to be added to the system
 */
void OrderManager::createOrder(const Order& order) {
    orders_.push_back(order);
}

/**
 * @brief Processes all orders stored in the OrderManager.
 * 
 * This function iterates through all orders in the orders_ container and prints
 * each order to the standard output. The output includes a header message and
 * each order's details on a new line.
 * 
 * @note This method currently only displays orders and doesn't perform any
 * actual processing logic beyond printing.
 */
void OrderManager::processAllOrders() {
    std::cout << "[+] Processing all orders...\n";
    std::for_each(orders_.begin(), orders_.end(), [](Order& o){
        std::cout << o << "\n";
    });
}
