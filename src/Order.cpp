#include "Order.hpp"
#include "Product.hpp"
#include "Warehouse.hpp" // Required for Warehouse class definition for totalPrice
#include <numeric>       // For std::accumulate
#include <iostream>      // For std::cerr in totalPrice (optional error logging)

/**
 * @brief Adds a product to the order or increases its quantity if it already exists.
 * * This method adds a specified quantity of a product to the order. If the product
 * is already in the order, the quantity is increased by the specified amount.
 * Otherwise, a new entry is created with the given quantity.
 * * @param product The product to add to the order.
 * @param quantity The quantity of the product to add. Must be positive.
 */
void Order::addItem(const Product& product, int quantity) {
    if (quantity <= 0)
    {
        // Optionally, handle this error, e.g., by logging or throwing an exception
        std::cerr << "Warning: Attempted to add non-positive quantity (" << quantity
                  << ") for product ID " << product.getId() << ". Action ignored." << std::endl;
        return;
    }
    auto it = items_.find(product.getId());
    if (it != items_.end()) {
        it->second += quantity;
    } else {
        items_[product.getId()] = quantity;
    }
}

/**
 * @brief Calculates the total price of all items in the order
 * * This method iterates through all items in the order and calculates the sum
 * of their prices by finding each product in the provided warehouse and
 * multiplying its price by the quantity ordered. Uses std::accumulate.
 * * @param warehouse The Warehouse object used to find product details (like price).
 * @return double The total price of the entire order.
 */
double Order::totalPrice(const Warehouse &warehouse) const
{
    return std::accumulate(items_.begin(), items_.end(), 0.0,
                           [&warehouse](double current_sum, const std::pair<const int, int> &item_pair)
                           {
                               int product_id = item_pair.first;
                               int quantity = item_pair.second;

                               auto product_expected = warehouse.findProductById(product_id);
                               if (product_expected)
                               {                                         // Check if std::expected has a value
                                   const Product *p = *product_expected; // or product_expected.value()
                                   return current_sum + (p->getPrice() * quantity);
                               }
                               else
                               {
                                   // Product not found in warehouse, log error and continue sum
                                   std::cerr << "Error in totalPrice: Product with ID " << product_id
                                             << " not found in warehouse. Details: " << product_expected.error()
                                             << ". This item's price will not be added to total." << std::endl;
                                   return current_sum;
                               }
                           });
}

/**
 * @brief Returns the number of unique product types in the order
 * @return The number of unique product types in the order
 */
size_t Order::itemCount() const {
    return items_.size();
}

/**
 * @brief Overloaded stream insertion operator for Order class
 * * Outputs the details of an order including all product IDs and their quantities.
 * Format:
 * [+] Order details:
 * - ID: {id} | Quantity:  x {quantity}
 * - ID: {id} | Quantity:  x {quantity}
 * ...
 *
 * @param os The output stream to write to
 * @param order The Order object to display
 * @return std::ostream& Reference to the output stream for chaining
 */
std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "[+] Order details:\n";
    if (order.items_.empty())
    {
        os << " - Order is empty.\n";
    }
    else
    {
        for (const auto &[prodId, qty] : order.items_)
        { // Use const auto&
            os << " - ID: " << prodId
               << " | Quantity:  x " << qty << "\n";
        }
    }
    return os;
}

/**
 * @brief Overloaded stream extraction operator for Order class
 *
 * Reads the details of an order from an input stream. The format is expected to be:
 * {n} (number of unique items)
 * {product_id_1} {quantity_1}
 * {product_id_2} {quantity_2}
 * ...
 * where {n} is the number of products in the order.
 *
 * @param is The input stream to read from
 * @param order The Order object to populate. Clears existing items.
 * @return std::istream& Reference to the input stream for chaining
 */
std::istream &operator>>(std::istream &is, Order &order)
{
    order.items_.clear(); // Clear previous items
    int n;
    is >> n;
    if (!is.good() || n < 0)
    {                                        // Basic validation
        is.setstate(std::ios_base::failbit); // Set failbit if count is invalid
        return is;
    }
    for (int i = 0; i < n; ++i)
    {
        int pid, qty;
        is >> pid >> qty;
        if (!is.good() || qty <= 0)
        {                                        // More validation
            is.setstate(std::ios_base::failbit); // Set failbit
            order.items_.clear();                // Ensure order is not partially filled on error
            return is;
        }
        order.items_[pid] = qty;
    }
    return is;
}

/**
 * @brief Removes an item from the order
 *
 * This method removes an item from the order with the specified product ID.
 *
 * @param productId The ID of the product to remove
 */
void Order::removeItem(int productId)
{
    items_.erase(productId); // erase on map by key
}

/**
 * @brief Edits the quantity of an item in the order
 *
 * This method changes the quantity of an item in the order with the specified
 * product ID. If the new quantity is zero or negative, the item is removed from the order.
 *
 * @param productId The ID of the product to edit
 * @param newQuantity The new quantity of the product
 */
void Order::editItemQuantity(int productId, int newQuantity)
{
    auto it = items_.find(productId);
    if (it != items_.end())
    {
        if (newQuantity <= 0)
        {
            items_.erase(it); // Remove item if new quantity is not positive
        }
        else
        {
            it->second = newQuantity;
        }
    }
    else if (newQuantity > 0)
    {
        // Optionally, if product ID not found, could add it as a new item.
        // For "edit", current behavior (do nothing if not found) is common.
        std::cerr << "Warning: Attempted to edit quantity for non-existent product ID "
                  << productId << " in order. Action ignored." << std::endl;
    }
}