#include "Margarita.hpp"

Margarita::~Margarita() {}

std::string Margarita::description() override
{
    std::cout << "Margarita's ingridiens: tomato sauce, basil, mozzarella";
}

double Margarita::cost() override
{
    return 12.50;
}
