#pragma once

#include "person.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

enum class Meal
{
    Breakfast,
    Dinner,
    Supper
};

constexpr size_t dayLifTime = 30;
constexpr size_t mealBreak = 10;

class Kitchen
{
public:
    Kitchen() = default;
    Kitchen(std::vector<Person *> vec, size_t mealDuration) : subscribers_(vec), mealDuration_(mealDuration) {}

    void attached(Person *person);

    bool detach(Person *person);

    void notify();

    void startMeal();

    void setMeal(Meal meal) {
        meal_ = meal;;
    }

    // static std::string getMeal()
    // {
    //     if (meal_ == Meal::Breakfast)
    //     {
    //         return "Breakfast";
    //     }
    //     else if (meal_ == Meal::Dinner)
    //     {
    //         return "Dinner";
    //     }

    //     return "Supper";
    // }
    void changeMeal() {
        Meal temp = meal_;
        if(temp == Meal::Breakfast) {
            meal_ = Meal::Dinner;
        } else if (temp == Meal::Dinner) {
            meal_ = Meal::Supper;
        } else {
            meal_ = Meal::Breakfast;
        }
    }
protected:
    std::vector<Person *> subscribers_;
    size_t mealDuration_ = 0;
    Meal meal_;
};