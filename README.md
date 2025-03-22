# SmartInventorySim

## Project Description

SmartInventorySim is a warehouse management system designed to help businesses manage their inventory efficiently. The system allows users to add, find, and sort products, create and process orders, and generate reports. The project includes various product types such as electronics, clothing, and food, each with specific attributes.

## Purpose and Functionality

The purpose of SmartInventorySim is to provide a comprehensive solution for managing warehouse inventory. The system offers the following functionalities:
- Add products to the warehouse
- Find products by name or ID
- Sort products by price
- Create and process customer orders
- Generate reports on warehouse inventory and orders

## Installation Instructions

### Prerequisites

Before you begin, ensure you have the following installed on your machine:
- C++ compiler (e.g., g++, clang++)
- CMake (version 3.20 or higher)
- Git

### Steps

1. Clone the repository:
   ```sh
   git clone https://github.com/MichalZak17/SmartInventorySim.git
   cd SmartInventorySim
   ```

2. Create a build directory and navigate to it:
   ```sh
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:
   ```sh
   cmake ..
   ```

4. Build the project:
   ```sh
   make
   ```

5. Run the executable:
   ```sh
   ./MyECommerceProject
   ```

## Examples and Usage Scenarios

### Adding Products

To add products to the warehouse, create instances of the product classes and add them to the warehouse:
```cpp
Warehouse warehouse;
warehouse.addProduct(std::make_unique<Electronic>("iPhone 16 Pro", 5299.99, 10000, 0.2, "2 years"));
warehouse.addProduct(std::make_unique<Clothing>("Nike Vomero 18", 499.99, 500, 0.5, "48"));
warehouse.addProduct(std::make_unique<Food>("Carrot Juice", 5.50, 200, 0.3, "2025-12-31"));
```

### Creating Orders

To create an order, instantiate the `Order` class and add items to it:
```cpp
Order order1;
order1.addItem(*warehouse.findProductByName("iPhone 16 Pro").value(), 2);
order1.addItem(*warehouse.findProductByName("Nike Vomero 18").value(), 1);
```

### Generating Reports

To generate a report, use the `OrderManager` class to process orders and export the report to a file:
```cpp
OrderManager orderManager;
orderManager.createOrder(order1);
orderManager.processAllOrders();

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
```

## Contribution Guidelines

We welcome contributions to SmartInventorySim! If you would like to contribute, please follow these guidelines:

1. Fork the repository and create a new branch for your feature or bugfix.
2. Write clear, concise commit messages.
3. Ensure your code follows the project's coding standards.
4. Write tests for your changes.
5. Submit a pull request with a detailed description of your changes.

## Contact Information

For any questions or inquiries, please contact Michał Żak at michal.zak@example.com.

## Cool Design and Layout

To make the `README.md` visually appealing, we have used the following design elements:
- Clear section headings
- Code blocks for commands and examples
- Bullet points for lists
- Consistent formatting throughout the document
