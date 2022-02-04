#include "cheesePizza.hpp"

CheesePizza::CheesePizza(Pizza *pizza) : pizza_(pizza) {}

std::string CheesePizza::description() override
{
    std::cout << pizza_->description() << " cheese";
}

double CheesePizza::cost() override
{
    return pizza_->cost() + 2.30;
}
