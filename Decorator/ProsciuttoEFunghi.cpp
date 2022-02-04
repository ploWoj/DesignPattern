#include "ProsciuttoEFunghi.hpp"

ProsciuttoEFunghi::ProsciuttoEFunghi(){};

double ProsciuttoEFunghi::cost() override
{
    return 17.30;
}

std::string ProsciuttoEFunghi::description() override
{
    std::cout << "ProsciuttoEFunghi ingridens: tomatoe sauce, mozzarella, ham, oregano, champigon"
}