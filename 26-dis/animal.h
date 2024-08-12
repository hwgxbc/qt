#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>
#include <iostream>

using namespace std;

class Animal
{
public:
    string name;
    int age;

    Animal();
    void makeSound();
    void eatFood();

};

#endif // ANIMAL_H
