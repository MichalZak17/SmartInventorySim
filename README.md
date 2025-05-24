# SmartInventorySim Warehouse Manager 🛒💻

## Table of Contents

  - [SmartInventorySim Warehouse Manager 🛒💻](https://www.google.com/search?q=%23smartinventorysim-warehouse-manager-)
      - [Table of Contents](https://www.google.com/search?q=%23table-of-contents)
      - [Project Description](https://www.google.com/search?q=%23project-description)
      - [Purpose and Functionality](https://www.google.com/search?q=%23purpose-and-functionality)
      - [University Requirements Met](https://www.google.com/search?q=%23university-requirements-met)
      - [Installation and Execution Instructions](https://www.google.com/search?q=%23installation-and-execution-instructions)
          - [Prerequisites](https://www.google.com/search?q=%23prerequisites)
          - [Steps](https://www.google.com/search?q=%23steps)
      - [Application Usage Examples](https://www.google.com/search?q=%23application-usage-examples)
          - [Interactive Menu](https://www.google.com/search?q=%23interactive-menu)
          - [Adding Products (programmatically)](https://www.google.com/search?q=%23adding-products-programmatically)
          - [Creating Orders (programmatically)](https://www.google.com/search?q=%23creating-orders-programmatically)
      - [Contributing](https://www.google.com/search?q=%23contributing)
      - [Contact](https://www.google.com/search?q=%23contact)
      - [License](https://www.google.com/search?q=%23license)

-----

## Project Description

**SmartInventorySim** is a warehouse management system simulator written in C++. It is designed to demonstrate advanced object-oriented programming concepts and modern C++ techniques. The system allows for managing various product types (electronics, clothing, food), handling orders, and file operations. The main focus is on data processing and simulation of warehouse operations, not just information storage.

-----

## Purpose and Functionality

The main purpose of SmartInventorySim is to provide a comprehensive C++ application example that meets specific academic requirements, demonstrating best practices and modern language features.

Key functionalities of the system:

  - **Product Management:**
      - Adding new products of different types (Electronics, Clothing, Food) manually or from a file.
      - Each product has a unique ID, name, price, quantity, and type-specific attributes (e.g., warranty, size, expiration date).
      - Displaying information about products in the warehouse.
      - Sorting products (e.g., by price).
      - Saving the warehouse state to a file.
      - Periodic price updates in the warehouse (e.g., a 1% reduction using the overloaded `operator()`).
  - **Order Management:**
      - Creating new orders, including generating random orders based on available products.
      - Editing existing orders: adding/removing items, changing quantities.
      - Deleting orders.
      - Displaying all orders along with their total price.
      - "Processing" all orders (currently involves displaying them).
  - **File Handling:**
      - Loading product definitions from a text file.
      - Saving the current warehouse state to a text file. The save format correctly parses strings containing spaces (using `std::quoted`).
  - **Random Data Generation:**
      - Use of random number generators and distributions to create orders.

-----

## University Requirements Met

The project was developed considering the following academic requirements:

1.  📦 **Core C++ Concepts:**

      * **Function Overloading:** Present (implicitly through copy/move constructors).
      * **References:** Widely used throughout the code.
      * **Constructors with Initializer Lists:** Used in all classes.
      * **Copy Constructors:** Defined for `TangibleProduct`.
      * **Object Aggregation (has-a):** E.g., `Warehouse` contains products, `Order` contains order items.
      * **Destructors:** Virtual destructors in base classes (`Product`, `TangibleProduct`) for proper memory management.
      * **Constant Methods (`const` methods):** Many `get` methods and `printInfo`.
      * **Constant Attributes (`const` attributes):** Not explicitly used, but `const&` references are common.
      * **`mutable` Attributes:** `Warehouse::accessCount_` for tracking access in `const` methods.
      * **Static Objects/Attributes in Class:** `Product::globalIdCounter_`, `RandomGenerator::getEngine()`.
      * **Friendship (`friend`):** Stream operators `<<` and `>>` are friends with their respective classes.
      * **Operator Overloading:**
          * `operator=`: Copy and move assignment for `TangibleProduct`.
          * `operator<<`: For `Product`, `Order` for display.
          * `operator>>`: For `Product` and derivatives (for file/console input) and `Order`.
          * `operator()`: For `Warehouse` to simulate periodic updates.
          * `operator<=>` (spaceship): For `Product` for comparison.
      * **Nested Classes:** `Product::Details`.

2.  🚚 **Move Semantics:**

      * **Move Constructor:** Implemented for `TangibleProduct`.
      * **Move Assignment Operator:** Implemented for `TangibleProduct`.
      * Extensive use of `std::unique_ptr` and `std::move` ensures efficient resource management.

3.  🏛️ **Inheritance and Polymorphism:**

      * **Multi-level Inheritance (\>2 levels):** `Product` (abstract) -\> `TangibleProduct` -\> `Electronic` / `Clothing` / `Food`.
      * **Abstract Base Class:** `Product` with a pure virtual function `printInfo()`.
      * **Polymorphism:** Utilized, e.g., in `Warehouse` storing `std::vector<std::unique_ptr<Product>>` and calling virtual methods.

4.  🧠 **Functional Programming & Smart Pointers:**

      * **Standard Function Objects:** Use of lambda expressions with STL algorithms (`std::sort`, `std::find_if`, `std::for_each`, `std::accumulate`).
      * **Custom Function Objects:** `Warehouse::operator()`.
      * **Lambda Expressions:** Applied in many places, e.g., for sorting, searching, processing collections.
      * **Smart Pointers:** `std::unique_ptr` for managing product memory in the warehouse and during creation.

5.  🧺 **STL Containers & Algorithms:**

      * **Minimum two containers (sequential and associative):**
          * `std::vector` (sequential): `Warehouse::products_`, `OrderManager::orders_`.
          * `std::map` (associative): `Order::items_` for storing products in an order.
      * **`std::string`:** Used for storing names, descriptions, etc.
      * **Standard Library Algorithms:** `std::copy` (in `Utils`), `std::sort` (product sorting), `std::for_each` (container iteration), `std::find_if` (product searching), `std::accumulate` (calculating total order price).

6.  🎲 **Random Data Generation:**

      * `RandomGenerator` class using `std::mt19937` and distributions `std::uniform_int_distribution` and `std::uniform_real_distribution` for generating random data for simulation purposes (e.g., creating orders).

7.  🧩 **Template Functions:**

      * Template functions `Utils::printContainer` and `Utils::copyElements`.

8.  💾 **File Handling:**

      * Reading (`loadProductsFromFile`) and writing (`saveProductsToFile`) product data to/from text files.
      * Use of `std::ifstream` and `std::ofstream`.
      * Correct handling of strings with spaces using `std::quoted`.

9.  ✨ **Modern C++ Features (C++17/20/23):**

      * **`std::span<>`:** Used in `Warehouse::printProductsInfo` to pass a view over a product collection.
      * **`std::optional<>`:** Returned by `Warehouse::findProductByName`.
      * **`std::expected<>`:** Returned by `Warehouse::findProductById` for error handling.

<!-- end list -->

  * **A. Data Processing Focus:** The program actively processes data (e.g., calculating prices, modifying inventory levels, simulating price changes).
  * **B. Simulation Character:** The program has simulation elements (e.g., random order generation, automatic price reduction). The console user interface serves for interaction and demonstration of these mechanisms.

-----

## Installation and Execution Instructions

### Prerequisites

Ensure you have the following tools installed:

  - A modern C++ compiler (supporting at least C++20 for `std::span`, `std::expected`, etc. - the project uses them).
  - CMake (version 3.15 or newer).
  - Git (for cloning the repository).
  - Optionally `conda` for environment management (as in the example).

### Steps

1.  Clone the repository (replace the URL with the actual URL of your repository):

    ```sh
    git clone <YOUR_SmartInventorySim_REPOSITORY_URL>
    cd SmartInventorySim
    ```

2.  (Optional, if using `conda`) Create and activate a new conda environment:

    ```sh
    conda create --name smartinventorysim_env cmake cxx-compiler
    conda activate smartinventorysim_env
    ```

    *Note: `cxx-compiler` is a conda-forge metapackage; alternatively, install a compiler system-wide (e.g., g++, clang++).*

3.  Create a build directory and navigate to it:

    ```sh
    mkdir build
    cd build
    ```

4.  Run CMake to configure the project (ensure your `CMakeLists.txt` is correctly configured to use C++20 or later):

    ```sh
    # If CMakeLists.txt is in the project's root directory:
    cmake .. 
    # You might need to specify the C++ standard, e.g.:
    # cmake .. -DCMAKE_CXX_STANDARD=20 
    ```

5.  Compile the project:

    ```sh
    cmake --build .
    # Alternatively, using make (on Unix-like systems):
    # make
    ```

6.  Run the executable (the name may depend on your CMake configuration, e.g., `SmartInventorySim` or `main`):

    ```sh
    ./SmartInventorySim 
    # Or e.g., ./main if that's how you named the target in CMake
    ```

-----

## Application Usage Examples

### Interactive Menu

Upon running the application, the user is greeted with an interactive console menu that allows for:

  - Displaying products in the warehouse.
  - Adding new products manually (for strings with spaces, quotes must be used, e.g., `"Laptop Pro"`).
  - Loading products from a file (e.g., `data/input_data.txt`).
  - Saving products to a file (e.g., `data/output_data.txt`).
  - Creating random orders.
  - Editing, deleting, and displaying orders.
  - Reducing product prices in the warehouse.

### Adding Products (programmatically)

Example of adding products directly in the code (as in `main()`):

```cpp
Warehouse warehouse;
// Names and string attributes containing spaces are valid.
// When loading from a file or entering manually, they will require quotes.
warehouse.addProduct(std::make_unique<Electronic>("Super Laptop X2000", 2999.99, 50, 1.5, "3 years warranty"));
warehouse.addProduct(std::make_unique<Clothing>("Stylish Silk Shirt", 120.00, 150, 0.2, "L"));
warehouse.addProduct(std::make_unique<Food>("Organic Avocado", 2.50, 300, 0.15, "2025-10-20"));
```

### Creating Orders (programmatically)

Example of creating an order and adding products to it (assuming `warehouse` and products exist):

```cpp
OrderManager orderManager;
Order newOrder;

// Find products (ensure the product exists and handle std::optional/std::expected)
auto laptop_opt = warehouse.findProductByName("Super Laptop X2000");
auto shirt_opt = warehouse.findProductByName("Stylish Silk Shirt");

if (laptop_opt && *laptop_opt) { // Check optional and pointer
    newOrder.addItem(**laptop_opt, 1); // Add 1 laptop
}
if (shirt_opt && *shirt_opt) {
    newOrder.addItem(**shirt_opt, 3); // Add 3 shirts
}

if (newOrder.itemCount() > 0) {
    orderManager.createOrder(newOrder);
}
```

-----

## Contributing

Contributions are welcome\! If you want to contribute:

1.  Fork the repository.
2.  Create a new branch (`git checkout -b feature/YourChange`).
3.  Implement your changes.
4.  Commit your changes (`git commit -m 'Add YourChange'`).
5.  Push your changes to your branch (`git push origin feature/YourChange`).
6.  Open a Pull Request.

-----

## Contact

Michał Żak
[michal.zak000@gmail.com](mailto:michal.zak000@gmail.com)

-----

## License

Distributed under the MIT License. See `LICENSE` for more information.

-----