#pragma once
#include "pizza.hpp"
#include "pizzasDecorator.hpp"

struct CheesePizza : PizzasDecorator
{
    Pizza *pizza_;
    CheesePizza(Pizza *pizza);
    std::string description() override;
    double cost() override;
};