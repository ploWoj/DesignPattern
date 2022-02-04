#include <iostream>
#include <string>

typedef int Cable; // wire

class EuropeanSocketInterface
{
public:
    virtual int voltage() = 0;
    virtual Cable live() = 0;
    virtual Cable neutral() = 0;
    virtual Cable earth() = 0;
};

class Socket : public EuropeanSocketInterface
{
public:
    int voltage()
    {
        return 230;
    }

    Cable live() override
    {
        return 1;
    }

    Cable neutral() override
    {
        return -1;
    }
    Cable earth() override
    {
        return 0;
    }
};