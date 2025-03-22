#ifndef FOOD_HPP
#define FOOD_HPP

#include "TangibleProduct.hpp"
#include <string>

class Food : public TangibleProduct {
    std::string expirationDate_; // e.g. "2025-12-31"

public:
    Food(const std::string& name, double price, int quantity,
         double weight, const std::string& expirationDate);

    void printInfo() const override;
};

#endif
