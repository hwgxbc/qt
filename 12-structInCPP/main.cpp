#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

class Car{       //汽车“类”

public:
    string color;  //颜色
    string brand;  //品牌
    string type;   //车型
    int year;     //年限

    void (*printCarInfo)(string color,string brand,string type, int year); //函数指针，指向车介绍函数
    void (*carRun)(string type);       //函数指针，指向车运行的函数
    void (*carStop)(string type);      //函数指针，执行车停止的函数
};

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

    BWMthree.printCarInfo = bwmThreePrintCarInfo;
    BWMthree.printCarInfo(BWMthree.color,BWMthree.brand,BWMthree.type,BWMthree.year);

    Car *AodiA6 = new Car();
  //  AodiA6 = (struct Car*)malloc(sizeof(struct Car));


    AodiA6->color = "黑色";
    AodiA6->brand = "奥迪";
    AodiA6->type = "A6";
    AodiA6->year = 2008;
    AodiA6->printCarInfo = A6PrintCarInfo;

    AodiA6->printCarInfo(AodiA6->color,AodiA6->brand,AodiA6->type,AodiA6->year);

    return 0;
}

