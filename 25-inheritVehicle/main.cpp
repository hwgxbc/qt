#include <iostream>
using namespace std;

//基类，父类
class Vehicle{ //交通工具，车,抽象的概念
public:
    string type;
    string contry;
    string color;
    double price;
    int numOfWheel;

    void run(){
        cout << "车跑起来了" << endl;
    }
    void stop();
};

//派生类，子类
class Bickle : public Vehicle{

};

//派生类，子类
class Roadster : public Vehicle{ //跑车，也是抽象，比父类感觉上范围缩小了点
public:
    int stateOfTop;

    void openTopped();
    void pdrifting();
};

int main()
{
    Roadster ftype;
    ftype.type = "捷豹Ftype";
    ftype.run();
    Bickle bike;
    bike.type = "死飞";
    bike.run();
    return 0;
}
