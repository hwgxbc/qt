#include <stdio.h>
#include <stdlib.h>

struct Car{       //汽车“类”
    char *color;  //颜色
    char *brand;  //品牌
    char *type;   //车型
    int year;     //年限

    void (*printCarInfo)(char *color,char *brand,char *type, int year); //函数指针，指向车介绍函数
    void (*carRun)(char *type);       //函数指针，指向车运行的函数
    void (*carStop)(char *type);      //函数指针，执行车停止的函数
};

void bwmThreePrintCarInfo(char *color,char *brand,char *type, int year)
{
    printf("车的品牌是：%s, 型号是: %s, 颜色是：%s,上市年限是%d\n",
           brand,type,color,year);
}
void A6PrintCarInfo(char *color,char *brand,char *type, int year)
{
    printf("车的品牌是：%s,型号是: %s, 颜色是：%s, 上市年限是%d\n",
           brand,type,color,year);
}

int main()
{
    struct Car BWMthree;
    BWMthree.color = "白色";
    BWMthree.brand = "宝马";
    BWMthree.type  = "3系";
    BWMthree.year  = 2023;

    BWMthree.printCarInfo = bwmThreePrintCarInfo;
    BWMthree.printCarInfo(BWMthree.color,BWMthree.brand,BWMthree.type,BWMthree.year);

    struct Car *AodiA6;
    AodiA6 = (struct Car*)malloc(sizeof(struct Car));

    AodiA6->color = "黑色";
    AodiA6->brand = "奥迪";
    AodiA6->type = "A6";
    AodiA6->year = 2008;

    AodiA6->printCarInfo = A6PrintCarInfo;
    AodiA6->printCarInfo(AodiA6->color,AodiA6->brand,AodiA6->type,AodiA6->year);
    return 0;
}
