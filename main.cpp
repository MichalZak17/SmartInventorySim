#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <memory> // unique_ptr
#include <vector>
#include <iomanip>   // For std::quoted
#include <algorithm> // For std::for_each

#include "Warehouse.hpp"
#include "OrderManager.hpp"
#include "Electronic.hpp"
#include "Clothing.hpp"
#include "Food.hpp"
#include "RandomGenerator.hpp"

/**
 * @brief Function to clear the input stream.
 *
 * This function clears the input stream and ignores any remaining characters.
 */
static void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Function to create a new product based on user input.
 *
 * This function displays a menu to the user to select a product type
 * and then reads the product details from the user. It returns a unique
 * pointer to the created product.
 *
 * @return std::unique_ptr<Product> A unique pointer to the created product
 *
 */
std::unique_ptr<Product> createProductFromUser()
{
    std::cout << "Select product type:\n";
    std::cout << "1. Electronic\n";
    std::cout << "2. Clothing\n";
    std::cout << "3. Food\n";
    std::cout << "Your choice: ";
    int choice;
    std::cin >> choice;
    clearInput(); // Clear the newline character after reading int

    // Create an empty object of the target type and read data using operator>>
    // (defined in derived classes)
    switch (choice)
    {
    case 1:
    {
        auto e = std::make_unique<Electronic>("tmp", 0.0, 0, 0.0, "no-warranty");
        std::cout << "Enter data for Electronic: [\"name\" price quantity weight \"warranty\"]\n(Note: strings with spaces must be quoted, e.g., \"Laptop X1\" or \"2 years\")\n> ";
        std::cin >> *e;
        if (!std::cin.good())
        {
            clearInput();
            std::cerr << "Invalid data!\n";
            return nullptr; // Return nullptr on bad input
        }
        clearInput(); // Clear any remaining input on the line
        return e;
    }
    case 2:
    {
        auto c = std::make_unique<Clothing>("tmp", 0.0, 0, 0.0, "M");
        std::cout << "Enter data for Clothing: [\"name\" price quantity weight \"size\"]\n(Note: strings with spaces must be quoted, e.g., \"Blue Jeans\" or \"XL\")\n> ";
        std::cin >> *c;
        if (!std::cin.good())
        {
            clearInput();
            std::cerr << "Invalid data!\n";
            return nullptr; // Return nullptr on bad input
        }
        clearInput(); // Clear any remaining input on the line
        return c;
    }
    case 3:
    {
        auto f = std::make_unique<Food>("tmp", 0.0, 0, 0.0, "2099-12-31");
        std::cout << "Enter data for Food: [\"name\" price quantity weight \"expirationDate\"]\n(Note: strings with spaces must be quoted, e.g., \"Organic Apples\" or \"2025-12-31\")\n> ";
        std::cin >> *f;
        if (!std::cin.good())
        {
            clearInput();
            std::cerr << "Invalid data!\n";
            return nullptr; // Return nullptr on bad input
        }
        clearInput(); // Clear any remaining input on the line
        return f;
    }
    default:
        std::cerr << "Unknown option.\n";
        return nullptr;
    }
}

/**
 * @brief Load products from a file into the warehouse.
 *
 * This function reads product data from the specified file and adds them to the warehouse.
 * Each product line starts with the product type (Electronic, Clothing, or Food) followed by
 * the specific product attributes (name, price, quantity, weight, specific_attribute).
 * String attributes like name, warranty, size, expirationDate are expected to be quoted if they contain spaces.
 *
 * @param filename The path to the file to load products from
 * @param warehouse The Warehouse object to add products to
 */
void loadProductsFromFile(const std::string &filename, Warehouse &warehouse)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << filename << "\n";
        return;
    }

    std::string type;
    while (file >> type) // Read product type, loop continues if successful
    {
        if (type == "Electronic")
        {
            auto e = std::make_unique<Electronic>("", 0.0, 0, 0.0, "");
            file >> *e; // Uses Electronic::operator>>
            if (file.good())
            {
                warehouse.addProduct(std::move(e));
            }
            else if (!file.eof()) // Error occurred before EOF
            {
                std::cerr << "Error reading Electronic product data from file.\n";
                file.clear();                                                   // Clear error flags
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to next line
            }
        }
        else if (type == "Clothing")
        {
            auto c = std::make_unique<Clothing>("", 0.0, 0, 0.0, "M");
            file >> *c; // Uses Clothing::operator>>
            if (file.good())
            {
                warehouse.addProduct(std::move(c));
            }
            else if (!file.eof())
            {
                std::cerr << "Error reading Clothing product data from file.\n";
                file.clear();
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else if (type == "Food")
        {
            auto f = std::make_unique<Food>("", 0.0, 0, 0.0, "2099-01-01");
            file >> *f; // Uses Food::operator>>
            if (file.good())
            {
                warehouse.addProduct(std::move(f));
            }
            else if (!file.eof())
            {
                std::cerr << "Error reading Food product data from file.\n";
                file.clear();
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else
        {
            std::cerr << "Unknown product type in file: " << type << "\n";
            // Skip the rest of the line for unknown type
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    file.close();
    std::cout << "Products loaded from file: " << filename << "\n";
}

/**
 * @brief Saves all products from the warehouse to a file.
 *
 * This function writes the list of products stored in the given warehouse
 * to a text file. It uses dynamic_cast to determine the actual type of each product
 * (Electronic, Clothing, or Food) and writes their details to the file in a specific format.
 * String attributes are saved using std::quoted to handle spaces.
 *
 * The output format matches the format expected by the corresponding input operator (operator>>),
 * specifically: type_string "name" price quantity weight "specific_attribute".
 *
 * @param filename The name of the file to save the products to.
 * @param warehouse The warehouse containing the products to be saved.
 *
 * @note If the file cannot be opened, an error message will be printed to std::cerr.
 * @note Unknown product types will be ignored and not saved.
 */
void saveProductsToFile(const std::string &filename, const Warehouse &warehouse)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Cannot open file for writing: " << filename << "\n";
        return;
    }

    for (const auto &p_ptr : warehouse.getProducts())
    {
        if (const auto *ep = dynamic_cast<const Electronic *>(p_ptr.get()))
        {
            file << "Electronic "
                 << std::quoted(ep->getName()) << " "
                 << ep->getPrice() << " "
                 << ep->getQuantity() << " "
                 << ep->getWeight() << " "
                 << std::quoted(ep->getWarranty()) << "\n";
        }
        else if (const auto *cp = dynamic_cast<const Clothing *>(p_ptr.get()))
        {
            file << "Clothing "
                 << std::quoted(cp->getName()) << " "
                 << cp->getPrice() << " "
                 << cp->getQuantity() << " "
                 << cp->getWeight() << " "
                 << std::quoted(cp->getSize()) << "\n";
        }
        else if (const auto *fp = dynamic_cast<const Food *>(p_ptr.get()))
        {
            file << "Food "
                 << std::quoted(fp->getName()) << " "
                 << fp->getPrice() << " "
                 << fp->getQuantity() << " "
                 << fp->getWeight() << " "
                 << std::quoted(fp->getExpirationDate()) << "\n";
        }
        else
        {
            std::cerr << "Unknown product type encountered during save: product ID " << p_ptr->getId() << ". Skipping." << std::endl;
        }
    }

    file.close();
    std::cout << "Products saved to file: " << filename << "\n";
}

/**
 * @brief Main menu function to interact with the warehouse and order manager.
 *
 * This function displays a menu with various options to interact with the warehouse
 * and order manager. It allows the user to view products, add new products, create
 * orders, edit orders, and process orders.
 *
 * @param warehouse The Warehouse object to manage products
 * @param orderManager The OrderManager object to manage orders
 *
 * @note This function uses the standard input/output streams for user interaction.
 */
void runMenu(Warehouse &warehouse, OrderManager &orderManager)
{
    bool running = true;
    while (running)
    {
        std::cout << "\n================ MENU ================\n"
                  << "1. Display warehouse products\n"
                  << "2. Add new product (manually)\n"
                  << "3. Load products from file\n"
                  << "4. Save products to file\n"
                  << "5. Create new order (random)\n"
                  << "6. Edit order\n"
                  << "7. Delete order\n"
                  << "8. Process all orders\n"
                  << "9. Reduce prices in warehouse (operator())\n"
                  << "10. Display all orders\n"
                  << "0. Exit\n"
                  << "[?] Your choice: ";
        int choice;
        std::cin >> choice;
        if (!std::cin.good())
        {
            clearInput();
            std::cerr << "Invalid input.\n";
            continue;
        }
        clearInput(); // Clear newline after reading choice

        switch (choice)
        {
        case 0:
            running = false;
            break;

        case 1:
        {
            std::cout << "Warehouse products:\n";
            warehouse.printProductsInfo(warehouse.getProducts()); // getProducts() returns a vector, implicitly convertible to span
            break;
        }
        case 2:
        {
            auto product = createProductFromUser();
            if (product)
            {
                warehouse.addProduct(std::move(product));
                std::cout << "[+] New product added to the warehouse.\n";
            }
            break;
        }
        case 3:
        {
            std::cout << "Enter file name to load [e.g. data/input_data.txt]: ";
            std::string fname;
            std::getline(std::cin, fname); // Use getline to read filename with potential spaces, though unlikely needed here
            loadProductsFromFile(fname, warehouse);
            break;
        }
        case 4:
        {
            std::cout << "Enter file name to save [e.g. data/output_data.txt]: ";
            std::string fname;
            std::getline(std::cin, fname);
            saveProductsToFile(fname, warehouse);
            break;
        }
        case 5:
        {
            Order newOrder;
            const auto &prods = warehouse.getProducts(); // Use const auto&
            if (prods.empty())
            {
                std::cout << "Warehouse is empty. No products available for order!\n";
                break;
            }

            for (int i = 0; i < 3; i++) // Create an order with 3 random items
            {
                if (prods.empty())
                    break; // Should not happen if initial check passed but good for safety
                int idx = RandomGenerator::getRandomInt(0, static_cast<int>(prods.size()) - 1);
                int qty = RandomGenerator::getRandomInt(1, 5);
                newOrder.addItem(*prods[idx], qty);
            }
            if (newOrder.itemCount() > 0)
            {
                orderManager.createOrder(newOrder);
                std::cout << "Created an order with " << newOrder.itemCount() << " random product(s)!\n";
            }
            else
            {
                std::cout << "Could not create a random order (perhaps warehouse became empty).\n";
            }
            break;
        }
        case 6: // Edit order
        {
            auto &orders = orderManager.getOrders();
            if (orders.empty())
            {
                std::cout << "No orders to edit!\n";
                break;
            }
            std::cout << "Enter order index [0.."
                      << (orders.size() > 0 ? orders.size() - 1 : 0) << "]: ";
            size_t idx;
            std::cin >> idx;
            if (!std::cin.good() || idx >= orders.size())
            {
                clearInput();
                std::cerr << "Invalid index!\n";
                break;
            }
            clearInput(); // Clear newline

            Order &ord = orderManager.getOrder(idx);
            std::cout << "Editing order:\n"
                      << ord
                      << "\n--- Available actions ---\n"
                      << "1. Add item (productId, qty)\n"
                      << "2. Remove item (productId)\n"
                      << "3. Change quantity (productId, newQty)\n"
                      << "Other choice -> cancel\n"
                      << "Your choice: ";
            int subChoice;
            std::cin >> subChoice;
            if (!std::cin.good())
            {
                clearInput();
                break;
            }
            clearInput(); // Clear newline

            if (subChoice == 1)
            {
                std::cout << "Enter product ID and quantity:\n> ";
                int pid, q;
                std::cin >> pid >> q;
                if (!std::cin.good() || q <= 0)
                {
                    clearInput();
                    std::cerr << "Invalid product ID or quantity.\n";
                    break;
                }
                clearInput();
                auto result = warehouse.findProductById(pid);
                if (result) // std::expected has value
                {
                    ord.addItem(**result, q); // **result gives const Product&
                    std::cout << "Added to order.\n";
                }
                else
                {
                    std::cerr << "Error: " << result.error() << "\n";
                }
            }
            else if (subChoice == 2)
            {
                std::cout << "Enter product ID to remove:\n> ";
                int pid;
                std::cin >> pid;
                if (!std::cin.good())
                {
                    clearInput();
                    std::cerr << "Invalid product ID.\n";
                    break;
                }
                clearInput();
                ord.removeItem(pid);
                std::cout << "Removed from order.\n";
            }
            else if (subChoice == 3)
            {
                std::cout << "Enter product ID and new quantity:\n> ";
                int pid, newQty;
                std::cin >> pid >> newQty;
                if (!std::cin.good() || newQty < 0)
                { // Allow 0 to effectively remove or just disallow? For now, <0 is bad.
                    clearInput();
                    std::cerr << "Invalid product ID or quantity.\n";
                    break;
                }
                clearInput();
                ord.editItemQuantity(pid, newQty);
                std::cout << "Quantity changed.\n";
            }
            else
            {
                std::cout << "Cancelled.\n";
            }
            break;
        }
        case 7: // Delete order
        {
            auto &orders = orderManager.getOrders();
            if (orders.empty())
            {
                std::cout << "No orders to delete!\n";
                break;
            }
            std::cout << "Enter order index [0.."
                      << (orders.size() > 0 ? orders.size() - 1 : 0) << "]: ";
            size_t idx;
            std::cin >> idx;
            if (!std::cin.good() || idx >= orders.size())
            {
                clearInput();
                std::cerr << "Invalid index!\n";
            }
            else
            {
                clearInput();
                orderManager.removeOrder(idx);
                std::cout << "Order deleted.\n";
            }
            break;
        }
        case 8:
        {
            orderManager.processAllOrders();
            break;
        }
        case 9:
        {
            warehouse(); // Calls Warehouse::operator()
            std::cout << "Prices reduced by 1%.\n";
            break;
        }
        case 10:
        {
            const auto &orders = orderManager.getOrders(); // Use const auto&
            if (orders.empty())
            {
                std::cout << "No orders.\n";
            }
            else
            {
                size_t index = 0;
                std::for_each(orders.begin(), orders.end(), [&](const Order &o)
                              {
                    std::cout << "\n--- Order #" << index++ << " ---\n" << o; // operator<< for order already adds newline
                    // totalPrice now takes const Warehouse&
                    double tp = o.totalPrice(warehouse);
                    std::cout << "Total price: " << tp << "\n"; });
            }
            break;
        }
        default:
            std::cerr << "Unknown option.\n";
            break;
        }
    }
}

int main()
{
    Warehouse warehouse;
    OrderManager orderManager;

    // Example products
    // Note: Names with spaces like "Laptop Pro" and warranties like "2 years"
    // will be handled correctly by std::quoted during file I/O.
    // If adding manually via createProductFromUser, user needs to input them as "Laptop Pro", "2 years".
    warehouse.addProduct(std::make_unique<Electronic>("Laptop Pro", 4500.0, 10, 1.2, "2 years"));
    warehouse.addProduct(std::make_unique<Clothing>("Jeans", 150.0, 25, 0.4, "M"));
    warehouse.addProduct(std::make_unique<Food>("Yogurt", 3.5, 100, 0.2, "2024-10-01"));
    warehouse.addProduct(std::make_unique<Electronic>("Smartphone Alpha", 2100.0, 15, 0.15, "1 year warranty"));
    warehouse.addProduct(std::make_unique<Clothing>("Silk Scarf", 89.90, 30, 0.05, "One Size"));
    warehouse.addProduct(std::make_unique<Food>("Imported Cheese", 25.0, 50, 0.25, "2024-12-15"));

    /**
     * If we want to sort products by price, we can use:
     * warehouse.sortByPriceAscending();
     * std::cout << "\n--- Products sorted by price ---" << std::endl;
     * warehouse.printProductsInfo(warehouse.getProducts());
     */

    // Start the main menu
    runMenu(warehouse, orderManager);

    std::cout << "[+] Exiting the program..." << std::endl;
    return 0;
}