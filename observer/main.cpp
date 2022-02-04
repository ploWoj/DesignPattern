#include <iostream>

#include "father.hpp"
#include "kid.hpp"
#include "kitchen.hpp"
#include "person.hpp"


int main() {

    Kitchen kitchen;
    Person* son = new Kid("Adam");
    Person* dauther = new Kid("Anna");
    Person* father = new Father("Thomas");

    kitchen.attached(father);
    kitchen.attached(son);
    kitchen.attached(dauther);

    kitchen.startMeal();

    delete son;
    delete dauther;
    delete father;

    return 0;
}