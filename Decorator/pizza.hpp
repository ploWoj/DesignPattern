#pragma once
#include <iostream>

struct Pizza
{
    virtual ~Pizza(){};
    virtual std::string description() = 0;
    virtual double cost() = 0;
};