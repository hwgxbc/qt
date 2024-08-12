#include <iostream>
using namespace std;

//基类，父类
class Vehicle{ //交通工具，车,抽象的概念
public:
    string contry;
    double price;

    Vehicle(string contry, double price){
        cout << "基类的构造函数被调用" << endl;
        this->contry = contry;
        this->price = price;
    };

    void run(){
        cout << "车跑起来了" << endl;
    }
    void stop();
};


//派生类，子类
class Roadster : public Vehicle{ //跑车，也是抽象，比父类感觉上范围缩小了点
public:
    int stateOfTop;
    Roadster(string contry, double price, int state) : Vehicle(contry, price){
        cout << "派生类的构造函数被调用" << endl;
        stateOfTop = state;
    }

    void openTopped();
    void pdrifting();
};

int main()
{

    Roadster FTYPE("法国",70,0);
    return 0;
}
