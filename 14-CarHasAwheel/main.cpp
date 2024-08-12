#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

class Wheel
{
public:
    string brand;
    int year;

    void wheelPrintInfo();
};

void Wheel::wheelPrintInfo()
{
    cout << "我的轮胎品牌是：" << brand << endl;
    cout << "我的轮胎日期是：" << year  << endl;
}

//在 C++中，一个类包含另一个类的对象称为组合（Composition）。
class Car{       //汽车“类”

public:
    //成员数据
    string color;  //颜色
    string brand;  //品牌
    string type;   //车型
    int year;     //年限

    Wheel wl;
    Wheel *pwl;

    //其实也是成员数据，指针变量，指向函数的变量，并非真正的成员函数
    void (*printCarInfo)(string color,string brand,string type, int year); //函数指针，指向车介绍函数
    void (*carRun)(string type);       //函数指针，指向车运行的函数
    void (*carStop)(string type);      //函数指针，执行车停止的函数

    void realPrintCarInfo();//声明成员函数

};

void Car::realPrintCarInfo() //在类的外部进行成员函数的实现
{
    string str = "车的品牌是：" + brand
            + ",型号是: " + type
            + ",颜色是：" + color
            + ",上市年限是:" + std::to_string(year);
    cout << str << endl;
}

void bwmThreePrintCarInfo(string color,string brand,string type, int year)
{
    string str = "车的品牌是：" + brand
            + ",型号是: " + type
            + ",颜色是：" + color
            + ",上市年限是:" + std::to_string(year);
    cout << str << endl;
}
void A6PrintCarInfo(string color,string brand,string type, int year)
{
    string str = "车的品牌是：" + brand
            + ",型号是: " + type
            + ",颜色是：" + color
            + ",上市年限是:" + std::to_string(year);
    cout << str << endl;
}

int main()
{
    Car BWMthree;
    BWMthree.color = "白色";
    BWMthree.brand = "宝马";
    BWMthree.type  = "3系";
    BWMthree.year  = 2023;

    BWMthree.pwl = new Wheel();
    BWMthree.pwl->brand = "米其林";
    BWMthree.pwl->year = 2023;
    //BWMthree.wl.brand = "米其林";
    //BWMthree.wl.year = 2023;

    BWMthree.printCarInfo = bwmThreePrintCarInfo;
    BWMthree.printCarInfo(BWMthree.color,BWMthree.brand,BWMthree.type,BWMthree.year);
    BWMthree.realPrintCarInfo();
    //BWMthree.wl.wheelPrintInfo();

    Car *AodiA6 = new Car();
  //  AodiA6 = (struct Car*)malloc(sizeof(struct Car));


    AodiA6->color = "黑色";
    AodiA6->brand = "奥迪";
    AodiA6->type = "A6";
    AodiA6->year = 2008;
    AodiA6->printCarInfo = A6PrintCarInfo;

    AodiA6->pwl = new Wheel;
    AodiA6->pwl->brand = "普利司通";
    AodiA6->pwl->year = 2012;

    //AodiA6->wl.brand = "马牌";
    //AodiA6->wl.year = 2023;

    AodiA6->printCarInfo(AodiA6->color,AodiA6->brand,AodiA6->type,AodiA6->year);
    AodiA6->realPrintCarInfo();
    //AodiA6->wl.wheelPrintInfo();
    AodiA6->pwl->wheelPrintInfo();
    delete(AodiA6->pwl);
    delete(AodiA6);
    return 0;
}


