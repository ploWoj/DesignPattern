#pragma once

#include <iostream>
#include "person.hpp"
#include "kitchen.hpp"

class Father : public Person {
public:
    Father(std::string name) : Person(name) {};
    ~Father() override = default;

    void react() override {
        std::cout << "Kids is the time for meal " << " !!!!";
    }
};