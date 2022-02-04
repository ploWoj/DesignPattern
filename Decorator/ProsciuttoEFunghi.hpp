#pragma once

#include "pizza.hpp"

struct ProsciuttoEFunghi : Pizza
{
    ProsciuttoEFunghi();
    std::string description() override;
    double cost() override;
};