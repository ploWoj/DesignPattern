#include "hamPizza.hpp"

HamPizza::HamPizza(Pizza *pizza) : pizza_(pizza) {}
HamPizza::~HamPizza(){};

double HamPizza::cost() override
{
    return pizza_->cost() + 3.20;
}
std::string HamPizza::description() override
{
    pizza_->description() + " hum";
}