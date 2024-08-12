#ifndef LION_H
#define LION_H

#include "animal.h"

class Lion : public Animal
{
public:
    int sleepingTime;

    Lion();
    void hunting();
};

#endif // LION_H
