#include <iostream>
using namespace std;

//基类，父类
class Vehicle{ //交通工具，车,抽象的概念
public:
    string contry;
    double price;

    Vehicle(){};
    virtual ~Vehicle(){};
    Vehicle(string contry, double price){

        this->contry = contry;
        this->price = price;
    };

    //基类中声明了一个虚函数
    virtual void run(){
        cout << "车跑起来了" << endl;
    }
    virtual void stop();
};

class Bike : public Vehicle{

public:
    void run() override {
        cout << "脚踩自行车" << endl;
    }
};

int main()
{

    Bike b;
    b.run();
    return 0;
}
