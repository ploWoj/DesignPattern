#pragma once

#include "pizza.hpp"

struct PizzasDecorator : Pizza
{
    virtual std::string description() = 0;
    virtual double cost() = 0;
};