#include "Warehouse.hpp"
#include <algorithm> // For std::sort, std::find_if, std::for_each
#include <iostream>  // For std::cout, std::cerr (debugging/info)

/**
 * @brief Adds a product to the warehouse.
 *
 * This method takes ownership of a Product represented by a std::unique_ptr and stores it
 * in the warehouse. The use of std::unique_ptr ensures proper memory management by transferring
 * ownership to the products_ container.
 *
 * @param product A unique pointer to the Product to be added. The pointer should not be null.
 */
void Warehouse::addProduct(std::unique_ptr<Product> product) {
    if (product)
    { // Ensure product is not nullptr before adding
        products_.push_back(std::move(product));
    }
    else
    {
        std::cerr << "Warning: Attempted to add a null product to the warehouse." << std::endl;
    }
}

/**
 * @brief Finds a product in the warehouse by its name.
 * * This method searches the warehouse inventory for a product with the specified name
 * using std::find_if. Each call to this method increments an internal access counter.
 * * @param name The name of the product to find.
 * @return std::optional<const Product*> An optional containing a pointer to the found product,
 * or std::nullopt if no product with the given name exists in the warehouse.
 * * @note This is a const method that modifies the mutable accessCount_ member variable.
 */
std::optional<const Product*> Warehouse::findProductByName(const std::string& name) const {
    ++accessCount_; // mutable variable can be changed in const method
    auto it = std::find_if(products_.begin(), products_.end(),
                           [&name](const std::unique_ptr<Product> &p_ptr) { // Capture name by reference
                               return p_ptr && p_ptr->getName() == name;    // Add null check for p_ptr
                           });
    if (it != products_.end()) {
        return it->get(); // Returns const Product*
    }
    return std::nullopt;
}

/**
 * @brief Searches for a product with the specified ID in the warehouse.
 *
 * This method iterates through the products in the warehouse using std::find_if
 * and returns a product pointer wrapped in std::expected if found, or an error message
 * if not found. The returned pointer points to the product owned by the
 * warehouse and should not be deleted by the caller.
 *
 * @param id The ID of the product to find.
 * @return std::expected<const Product*, std::string> The product (const Product*) if found,
 * or an error message string if no product with the given ID exists.
 */
std::expected<const Product *, std::string> Warehouse::findProductById(int id) const
{
    auto it = std::find_if(products_.begin(), products_.end(),
                           [id](const std::unique_ptr<Product> &p_ptr) // Capture id by value
                           {
                               return p_ptr && p_ptr->getId() == id; // Add null check for p_ptr
                           });
    if (it != products_.end()) {
        return it->get(); // Returns const Product*
    }
    else
    {
        return std::unexpected(std::string("Product with ID=") + std::to_string(id) + " not found");
    }
}

/**
 * @brief Prints information about all products in the given span.
 *
 * This method iterates through each product in the provided span using std::for_each
 * and calls the printInfo() method on each product to display its information.
 *
 * @param products_span A span of const unique_ptr<Product> objects whose
 * information will be printed.
 */
void Warehouse::printProductsInfo(std::span<const std::unique_ptr<Product>> products_span) const
{
    if (products_span.empty())
    {
        std::cout << "No products to display." << std::endl;
        return;
    }
    std::for_each(products_span.begin(), products_span.end(), [](const std::unique_ptr<Product> &p_ptr)
                  {
        if (p_ptr) { // Check if the pointer is not null
            p_ptr->printInfo();
        } });
}

/**
 * @brief Sorts the products in the warehouse by price in ascending order.
 * * This method uses std::sort with a lambda comparator to sort all products
 * based on their prices, from lowest to highest. If prices are equal,
 * the original relative order might not be preserved (std::sort is not guaranteed to be stable).
 * It relies on Product::operator<=> for comparison logic indirectly via getPrice().
 * * @note This operation modifies the order of products in the warehouse.
 */
void Warehouse::sortByPriceAscending() {
    std::sort(products_.begin(), products_.end(),
              [](const std::unique_ptr<Product> &a, const std::unique_ptr<Product> &b)
              {
                  if (!a || !b)
                      return false; // Handle nullptrs if they could exist, 'a' less than 'b' if 'b' is null
                  // For a more robust sort considering potential NaN or using spaceship:
                  // return (*a <=> *b) < 0; // If spaceship gives total order or partial that works for sort
                  // Simpler price comparison:
                  return a->getPrice() < b->getPrice();
              });
}

/**
 * @brief Operator() overload for the Warehouse class, used to execute periodic operations on products.
 * * This method iterates through all products stored in the warehouse using std::for_each
 * and updates their prices. Currently, it implements a simple pricing strategy
 * where each product's price is reduced by 1% in each execution cycle.
 * * Usage example:
 * Warehouse warehouse;
 * // ... add products ...
 * warehouse(); // Executes this operator, updating all product prices
 */
void Warehouse::operator()() {
    std::for_each(products_.begin(), products_.end(), [](std::unique_ptr<Product> &p_ptr)
                  {
        if (p_ptr) { // Check if the pointer is not null
            double currentPrice = p_ptr->getPrice();
            double newPrice = currentPrice * 0.99; // Reduce price by 1%
            p_ptr->setPrice(newPrice);
        } });
}