#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <filesystem>

#include "Electronic.hpp"
#include "Clothing.hpp"
#include "Food.hpp"
#include "Warehouse.hpp"
#include "Order.hpp"
#include "OrderManager.hpp"
#include "RandomGenerator.hpp"
#include "Utils.hpp"

int main() {

    std::cout << "[+] Welcome to the Warehouse Management System!" << std::endl; 

    std::cout << "[+] Initializing the warehouse..." << std::endl;

    // 1. Create a Warehouse
    Warehouse warehouse;

    std::cout << "[+] Adding products to the warehouse..." << std::endl;

    // 2. Add some random products
    warehouse.addProduct(std::make_unique<Electronic>("iPhone 16 Pro", 5299.99, 10000, 0.2, "2 years"));
    warehouse.addProduct(std::make_unique<Clothing>("Nike Vomero 18", 499.99, 500, 0.5, "48"));
    warehouse.addProduct(std::make_unique<Food>("Carrot Juice", 5.50, 200, 0.3, "2025-12-31"));
    warehouse.addProduct(std::make_unique<Electronic>("Samsung Galaxy S22", 3999.99, 8000, 0.2, "2 years"));
    warehouse.addProduct(std::make_unique<Clothing>("Adidas Ultraboost 22", 599.99, 300, 0.6, "44"));
    warehouse.addProduct(std::make_unique<Food>("Greek Yogurt", 3.99, 1000, 0.2, "2025-12-31"));

    // 3. Sort by ascending price and display
    warehouse.sortByPriceAscending();
    std::cout << "\n[+] Products after price sort (ascending):" << std::endl;
    warehouse.printProductsInfo(warehouse.getProducts());

    std::cout << "\n[+] Creating example order..." << std::endl;

    // 4. Create an order with random quantities
    Order order1;
    for (auto& prodPtr : warehouse.getProducts()) {
        int randQty = RandomGenerator::getRandomInt(1, 5);
        order1.addItem(*prodPtr, randQty);
    }

    std::cout << "\n[+] Order created successfully!" << std::endl;

    // 5. Compute total and display detailed order
    double totalOrderPrice = order1.totalPrice(warehouse.getProducts());
    std::cout << "\nOrder #1:\n";
    
    for (const auto& item : order1.getItems()) {
        auto prodOpt = warehouse.findProductById(item.first);
        if (prodOpt.has_value()) {
            const auto& prod = **prodOpt;
            std::cout << "[" << prod.getId() << "] " 
                      << prod.getName() << " [" 
                      << prod.getType() << "] Quantity x" 
                      << item.second << " - " 
                      << (prod.getPrice() * item.second) << " PLN\n";
        }
    }
    
    std::cout << "Total price: " << totalOrderPrice << " PLN\n\n";

    // 6. Use an OrderManager
    OrderManager orderManager;
    orderManager.createOrder(order1);

    // 7. Process all orders
    orderManager.processAllOrders();

    // 8. Example use of operator() in Warehouse
    warehouse();
    std::cout << "\n[+] After 1% price reduction (warehouse operator()):\n";
    warehouse.printProductsInfo(warehouse.getProducts());

    std::cout << "\n[+] Exporting warehouse and orders report..." << std::endl;

    // 9. Write a report to file    
    std::filesystem::create_directories("data"); // Create directory if it doesn't exist
    
    std::ofstream outFile("data/output_report.txt");
    if (outFile.is_open()) {
        outFile << "Warehouse and Orders Report\n\n";
        outFile << "Warehouse state:\n";
        for (auto& p : warehouse.getProducts()) {
            outFile << *p << "\n";
        }

        outFile << "\nOrders:\n";
        for (auto& o : orderManager.getOrders()) {
            outFile << o << "\n";
        }
        outFile.close();
    }
    

    // 10. Demo: findProductById with optional<>
    const auto id = 5;

    auto result = warehouse.findProductById(2);
    if (result.has_value()) {
        std::cout << "\nFound product with ID: " << id << ". " << **result << "\n";
    } else {
        std::cerr << "\nError: no product with ID=2\n";
    }

    return 0;
}