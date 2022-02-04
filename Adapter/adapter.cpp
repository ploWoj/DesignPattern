#include <iostream>
#include <string>

typedef int Cable; // wire
// Adaptee Interface
class EuropeanSocketInterface
{
public:
    virtual int voltage() = 0;
    virtual Cable live() = 0;
    virtual Cable neutral() = 0;
    virtual Cable earth() = 0;
};

// Adaptee
class Socket : public EuropeanSocketInterface
{
public:
    int voltage() override
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

// Target Interface
class AmericanSocetInterface
{
public:
    virtual int voltage() = 0;

    virtual Cable live() = 0;
    virtual Cable neutral() = 0;
};

// The Adapter

class Adapter : public AmericanSocetInterface
{
    EuropeanSocketInterface *socket_;

public:
    void plugIn(EuropeanSocketInterface *outlet)
    {
        socket_ = outlet;
    }

    int voltage() override
    {
        return 110;
    }

    Cable live() override
    {
        return socket_->live();
    }

    Cable neutral() override
    {
        return socket_->neutral();
    }
};

class ElectricKettle
{
    AmericanSocetInterface *power_;

public:
    void plugIn(AmericanSocetInterface *supply)
    {
        power_ = supply;
    }

    void boil()
    {
        if (power_->voltage() > 110)
        {
            std::cout << "Kettle is on fire" << '\n';
        }

        if (power_->live() == 1 && power_->neutral() == -1)
        {
            std::cout << "Coffee time!" << '\n';
        }
    }
};

int main()
{

    Socket *socket = new Socket;
    Adapter *adapter = new Adapter;
    ElectricKettle *kettle = new ElectricKettle;

    adapter->plugIn(socket);
    kettle->plugIn(adapter);
    kettle->boil();

    delete kettle;
    delete adapter;
    delete socket;

    return 0;
}
