#include "pizza.hpp"

struct Margarita : Pizza
{
    ~Margarita();
    std::string description() override;

    double cost() override;
};