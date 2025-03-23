#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <memory> // unique_ptr
#include <vector>

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
    clearInput();

    // Create an empty object of the target type and read data using operator>>
    // (defined in derived classes)
    switch (choice)
    {
    case 1:
    {
        auto e = std::make_unique<Electronic>("tmp", 0.0, 0, 0.0, "no-warranty");
        std::cout << "Enter data for Electronic: [name price quantity weight warranty]\n> ";
        std::cin >> *e;
        if (!std::cin.good())
        {
            clearInput();
            std::cerr << "Invalid data!\n";
        }
        return e;
    }
    case 2:
    {
        auto c = std::make_unique<Clothing>("tmp", 0.0, 0, 0.0, "M");
        std::cout << "Enter data for Clothing: [name price quantity weight size]\n> ";
        std::cin >> *c;
        if (!std::cin.good())
        {
            clearInput();
            std::cerr << "Invalid data!\n";
        }
        return c;
    }
    case 3:
    {
        auto f = std::make_unique<Food>("tmp", 0.0, 0, 0.0, "2099-12-31");
        std::cout << "Enter data for Food: [name price quantity weight expirationDate]\n> ";
        std::cin >> *f;
        if (!std::cin.good())
        {
            clearInput();
            std::cerr << "Invalid data!\n";
        }
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
 * the specific product attributes.
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

    while (!file.eof())
    {
        std::string type;
        file >> type;
        if (!file.good())
            break;

        if (type == "Electronic")
        {
            auto e = std::make_unique<Electronic>("", 0.0, 0, 0.0, "");
            file >> *e;
            if (file.good())
            {
                warehouse.addProduct(std::move(e));
            }
        }
        else if (type == "Clothing")
        {
            auto c = std::make_unique<Clothing>("", 0.0, 0, 0.0, "M");
            file >> *c;
            if (file.good())
            {
                warehouse.addProduct(std::move(c));
            }
        }
        else if (type == "Food")
        {
            auto f = std::make_unique<Food>("", 0.0, 0, 0.0, "2099-01-01");
            file >> *f;
            if (file.good())
            {
                warehouse.addProduct(std::move(f));
            }
        }
        else
        {
            std::cerr << "Unknown product type: " << type << "\n";
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
 *
 * The output format should match the format expected by the corresponding input operator (operator>>),
 * especially for more complex types like Electronic (e.g. warranty or additional attributes).
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

    // Simplified version: use dynamic_cast to recognize the type and save it
    for (auto &p : warehouse.getProducts())
    {
        if (auto ep = dynamic_cast<Electronic *>(p.get()))
        {
            file << "Electronic " << *ep << " " << ep->getWeight() << " "
                 << /* warranty – you must read/write in the same order as in operator>> */ "\n";
        }
        else if (auto cp = dynamic_cast<Clothing *>(p.get()))
        {
            file << "Clothing " << *cp << " " << cp->getWeight() << "\n";
        }
        else if (auto fp = dynamic_cast<Food *>(p.get()))
        {
            file << "Food " << *fp << " " << fp->getWeight() << "\n";
        }
        else
        {
            // Unknown type
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
 *      It may not handle invalid input gracefully.
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

        switch (choice)
        {
        case 0:
            running = false;
            break;

        case 1:
        {
            std::cout << "Warehouse products:\n";
            warehouse.printProductsInfo(warehouse.getProducts());
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
            std::cin >> fname;
            loadProductsFromFile(fname, warehouse);
            break;
        }
        case 4:
        {
            std::cout << "Enter file name to save [e.g. data/output_data.txt]: ";
            std::string fname;
            std::cin >> fname;
            saveProductsToFile(fname, warehouse);
            break;
        }
        case 5:
        {
            Order newOrder;
            auto &prods = warehouse.getProducts();
            if (prods.empty())
            {
                std::cout << "Warehouse is empty. No products available for order!\n";
                break;
            }

            for (int i = 0; i < 3; i++)
            {
                int idx = RandomGenerator::getRandomInt(0, (int)prods.size() - 1);
                int qty = RandomGenerator::getRandomInt(1, 5);
                newOrder.addItem(*prods[idx], qty);
            }
            orderManager.createOrder(newOrder);
            std::cout << "Created an order with 3 random products!\n";
            break;
        }
        case 6:
        {
            auto &orders = orderManager.getOrders();
            if (orders.empty())
            {
                std::cout << "No orders to edit!\n";
                break;
            }
            std::cout << "Enter order index [0.."
                      << orders.size() - 1 << "]: ";
            size_t idx;
            std::cin >> idx;
            if (idx >= orders.size())
            {
                std::cerr << "Invalid index!\n";
                break;
            }
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

            if (subChoice == 1)
            {
                std::cout << "Enter product ID and quantity:\n> ";
                int pid, q;
                std::cin >> pid >> q;
                auto result = warehouse.findProductById(pid);
                if (result)
                {
                    ord.addItem(**result, q);
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
                ord.removeItem(pid);
                std::cout << "Removed from order.\n";
            }
            else if (subChoice == 3)
            {
                std::cout << "Enter product ID and new quantity:\n> ";
                int pid, newQty;
                std::cin >> pid >> newQty;
                ord.editItemQuantity(pid, newQty);
                std::cout << "Quantity changed.\n";
            }
            else
            {
                std::cout << "Cancelled.\n";
            }
            break;
        }
        case 7:
        {
            auto &orders = orderManager.getOrders();
            if (orders.empty())
            {
                std::cout << "No orders to delete!\n";
                break;
            }
            std::cout << "Enter order index [0.."
                      << orders.size() - 1 << "]: ";
            size_t idx;
            std::cin >> idx;
            if (idx < orders.size())
            {
                orderManager.removeOrder(idx);
                std::cout << "Order deleted.\n";
            }
            else
            {
                std::cerr << "Invalid index!\n";
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
            warehouse();
            std::cout << "Prices reduced by 1%.\n";
            break;
        }
        case 10:
        {
            auto &orders = orderManager.getOrders();
            if (orders.empty())
            {
                std::cout << "No orders.\n";
            }
            else
            {
                for (size_t i = 0; i < orders.size(); ++i)
                {
                    std::cout << "\n--- Order #" << i << " ---\n"
                              << orders[i] << "\n";
                    double tp = orders[i].totalPrice(warehouse.getProducts());
                    std::cout << "Total price: " << tp << "\n";
                }
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
    warehouse.addProduct(std::make_unique<Electronic>("Laptop Pro", 4500.0, 10, 1.2, "2 years"));
    warehouse.addProduct(std::make_unique<Clothing>("Jeans", 150.0, 25, 0.4, "M"));
    warehouse.addProduct(std::make_unique<Food>("Yogurt", 3.5, 100, 0.2, "2024-10-01"));

    /**
     * If we want to sort products by price, we can use:
     * warehouse.sortByPriceAscending();
     */

    // Start the main menu
    runMenu(warehouse, orderManager);

    std::cout << "[+] Exiting the program..." << std::endl;
    return 0;
}