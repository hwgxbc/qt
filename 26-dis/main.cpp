#include <iostream>
#include "animal.h"
#include "lion.h"
#include "cat.h"

using namespace std;


int main()
{
    Animal a;
    a.makeSound();

    Lion l;
    l.makeSound();

    Cat c;
    c.eatFish();
    c.eatFood();
    return 0;
}
