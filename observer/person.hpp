#pragma once
#include <iostream>

class Person {
public: 
    Person(std::string name) : name_(name) {};
    virtual ~Person() = default;
    std::string getName() const {
        return name_;
    }

    virtual void react() = 0;
protected: 
    std::string name_;
};