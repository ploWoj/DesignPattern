#pragma once
#include <iostream>
#include "person.hpp"

class Kid : public Person {
public:
    Kid(std::string name) : Person(name) {} 
    ~Kid() override = default;
    void react() override {
        std::cout << "Heap heap hurray is 30 min break!!!!" << '\n';
    }
};