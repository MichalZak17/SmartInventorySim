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

/**
 * @brief Gets the collection of orders stored in the OrderManager.
 *
 * This method returns a reference to the internal orders_ container, allowing
 * external code to access and modify the orders stored in the OrderManager.
 *
 * @return A reference to the internal vector of Order objects
 */
Order &OrderManager::getOrder(size_t index)
{
    return orders_.at(index);
}

/**
 * @brief Removes an order from the OrderManager by index.
 *
 * This method removes the order at the specified index from the internal orders_
 * container. If the index is out of bounds, no action is taken.
 *
 * @param index The index of the order to remove
 */
void OrderManager::removeOrder(size_t index)
{
    if (index < orders_.size())
    {
        orders_.erase(orders_.begin() + index);
    }
}
