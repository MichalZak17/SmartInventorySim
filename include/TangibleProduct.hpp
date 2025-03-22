#ifndef TANGIBLEPRODUCT_HPP
#define TANGIBLEPRODUCT_HPP

#include "Product.hpp"

class TangibleProduct : public Product {
protected:
    double weight_;  // e.g. weight in kg

public:
    TangibleProduct(const std::string& name, double price, int quantity, double weight);
    virtual ~TangibleProduct();

    // Copy constructor
    TangibleProduct(const TangibleProduct& other);
    // Move constructor
    TangibleProduct(TangibleProduct&& other) noexcept;

    // Copy assignment
    TangibleProduct& operator=(const TangibleProduct& other);
    // Move assignment
    TangibleProduct& operator=(TangibleProduct&& other) noexcept;

    // Virtual method override
    virtual void printInfo() const override;

    double getWeight() const { return weight_; }
};

#endif
