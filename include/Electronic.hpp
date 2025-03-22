#ifndef ELECTRONIC_HPP
#define ELECTRONIC_HPP

#include "TangibleProduct.hpp"
#include <string>

class Electronic : public TangibleProduct {
    std::string warranty_; // e.g. "2 years"

public:
    Electronic(const std::string& name, double price, int quantity,
               double weight, const std::string& warranty);

    void printInfo() const override;
};

#endif
