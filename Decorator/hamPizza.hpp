#pragma once
#include "pizzasDecorator.hpp"

struct HamPizza : PizzasDecorator
{
    Pizza *pizza_;
    HamPizza(Pizza *pizza);
    ~HamPizza();
    double cost() override;
    std::string description() override;
};