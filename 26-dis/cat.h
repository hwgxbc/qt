#ifndef CAT_H
#define CAT_H

#include "animal.h"

class Cat : public Animal
{
public:
    Cat();

    void eatFish();
    void digAHole();
};

#endif // CAT_H
