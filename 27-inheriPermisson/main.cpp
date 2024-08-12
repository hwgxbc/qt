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
protected:
    int protectedData;
private:
    int privateData;

public:
    void run(){
        cout << "车跑起来了" << endl;
    }
    void stop();
};

//私有继承测试
class TestClass : private Vehicle{
public:
    void tsetFunc(){
        price = 10; //基类的公有数据被私有继承后，在派生类中权限编程私有，只限在类内部使用
    }
};
//公有继承测试
class Truck : protected Vehicle{

public:
    void testFunc(){
        type = "数据测试"; //编程了公有权限
        protectedData = 10; //保持公有权限
        privateData = 10; //报错了，基类的私有成员，不管哪种方式的继承都是不可访问的。
    }
};

//公有继承，基类的公有权限和保护权限不变，私有成员不能访问
class Bickle : public Vehicle{

public:
    void testFunc(){
        protectedData = 10;
    }
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
    TestClass test;
    test.price = 3.3; //报错了，基类的公有成员被私有继承后，降为私有权限

    Truck t;
    t.type = "测试"; //报错了，基类的公有成员被保护继承后，降为保护权限
    t.protectedData = 10; //从报错信息看出，保护继承造成基类的保护成员还是保持保护权限
    Roadster ftype;
    ftype.type = "捷豹Ftype";
    ftype.run();
    Bickle bike;
    bike.type = "死飞";
    bike.run();
    return 0;
}
