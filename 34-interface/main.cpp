
#include <iostream>

using namespace std;

class BasketBallMove{
  public:
    virtual void passTheBall() = 0;
};

class LiveMove{

public:
        virtual void eat() = 0;
        virtual void bite() = 0;
        virtual void drink() = 0;
        virtual void la() = 0;
};

class Human : public LiveMove,BasketBallMove{
public:
    void eat() override{};
    void bite() override{};
    void drink() override{};
    void la() override{};

    void passTheBall() override{};
};

class Dog : public LiveMove{
public:
    void eat() override{};
    void bite() override{};
    void drink() override{};
    void la() override{};
};

int main()
{
    Human h;
    Dog g;
  //  LiveMove *l = new LiveMove;
    return 0;
}
