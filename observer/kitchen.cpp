#include <chrono>
#include <thread>

#include "kitchen.hpp"


 void Kitchen::attached(Person* person)  {
        if(!person) {
            return;
        }
        subscribers_.push_back(person);
    }

 bool Kitchen::detach(Person* person)  {
        auto it = std::find(cbegin(subscribers_), cend(subscribers_), person );
        if (it != subscribers_.cend()) {
            subscribers_.erase(it);
            return true;
        }
        return false;
    }

void Kitchen::notify() {
    for (auto* el : subscribers_) {
        el->react();
    }
}

void Kitchen::startMeal() {
    while (mealDuration_ < mealBreak) {
        mealDuration_++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "| ";
        if (mealDuration_ % mealBreak == 0) {
            mealDuration_++;
            std::cout << '\n';
            this->notify();
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        changeMeal();
    }
    std::cout << "Koniec dnia:\n";
}