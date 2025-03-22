#include "Order.hpp"
#include "Product.hpp"

/**
 * @brief Adds a product to the order or increases its quantity if it already exists.
 * 
 * This method adds a specified quantity of a product to the order. If the product
 * is already in the order, the quantity is increased by the specified amount.
 * Otherwise, a new entry is created with the given quantity.
 * 
 * @param product The product to add to the order.
 * @param quantity The quantity of the product to add.
 */
void Order::addItem(const Product& product, int quantity) {
    auto it = items_.find(product.getId());
    if (it != items_.end()) {
        it->second += quantity;
    } else {
        items_[product.getId()] = quantity;
    }
}

/**
 * @brief Calculates the total price of all items in the order
 * 
 * This method iterates through all items in the order and calculates the sum
 * of their prices by finding each product in the warehouse inventory and 
 * multiplying its price by the quantity ordered.
 * 
 * @param warehouseProducts Vector of unique pointers to all available products in the warehouse
 * @return double The total price of the entire order
 */
double Order::totalPrice(const std::vector<std::unique_ptr<Product>>& warehouseProducts) const {
    double total = 0.0;
    for (auto& [id, qty] : items_) {
        // Find product by matching ID
        for (auto& p : warehouseProducts) {
            if (p->getId() == id) {
                total += p->getPrice() * qty;
                break;
            }
        }
    }
    return total;
}

/**
 * @brief Returns the number of items in the order
 * @return The number of items in the order
 */
size_t Order::itemCount() const {
    return items_.size();
}

/**
 * @brief Overloaded stream insertion operator for Order class
 * 
 * Outputs the details of an order including all product IDs and their quantities.
 * Format:
 * [+] Order details:
 *  - ID: {id}  x {quantity}
 *  - ID: {id}  x {quantity}
 *  ...
 *
 * @param os The output stream to write to
 * @param order The Order object to display
 * @return std::ostream& Reference to the output stream for chaining
 */
std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "[+] Order details:\n";
    for (auto& [prodId, qty] : order.items_) {
        os << " - ID: " << prodId
           << "| Quantity:  x " << qty << "\n";
    }
    return os;
}
