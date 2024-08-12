#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

class Car{       //�������ࡱ

public:
    //��Ա����
    string color;  //��ɫ
    string brand;  //Ʒ��
    string type;   //����
    int year;     //����
    //��ʵҲ�ǳ�Ա���ݣ�ָ�������ָ�����ı��������������ĳ�Ա����
    void (*printCarInfo)(string color,string brand,string type, int year); //����ָ�룬ָ�򳵽��ܺ���
    void (*carRun)(string type);       //����ָ�룬ָ�����еĺ���
    void (*carStop)(string type);      //����ָ�룬ִ�г�ֹͣ�ĺ���

    void realPrintCarInfo();//������Ա����

};

void Car::realPrintCarInfo() //������ⲿ���г�Ա������ʵ��
{
    string str = "����Ʒ���ǣ�" + brand
            + ",�ͺ���: " + type
            + ",��ɫ�ǣ�" + color
            + ",����������:" + std::to_string(year);
    cout << str << endl;
}

void bwmThreePrintCarInfo(string color,string brand,string type, int year)
{
    string str = "����Ʒ���ǣ�" + brand
            + ",�ͺ���: " + type
            + ",��ɫ�ǣ�" + color
            + ",����������:" + std::to_string(year);
    cout << str << endl;
}
void A6PrintCarInfo(string color,string brand,string type, int year)
{
    string str = "����Ʒ���ǣ�" + brand
            + ",�ͺ���: " + type
            + ",��ɫ�ǣ�" + color
            + ",����������:" + std::to_string(year);
    cout << str << endl;
}

int main()
{
    Car BWMthree;
    BWMthree.color = "��ɫ";
    BWMthree.brand = "����";
    BWMthree.type  = "3ϵ";
    BWMthree.year  = 2023;

    BWMthree.printCarInfo = bwmThreePrintCarInfo;
    BWMthree.printCarInfo(BWMthree.color,BWMthree.brand,BWMthree.type,BWMthree.year);
    BWMthree.realPrintCarInfo();

    Car *AodiA6 = new Car();
  //  AodiA6 = (struct Car*)malloc(sizeof(struct Car));


    AodiA6->color = "��ɫ";
    AodiA6->brand = "�µ�";
    AodiA6->type = "A6";
    AodiA6->year = 2008;
    AodiA6->printCarInfo = A6PrintCarInfo;

    AodiA6->printCarInfo(AodiA6->color,AodiA6->brand,AodiA6->type,AodiA6->year);
    AodiA6->realPrintCarInfo();
    return 0;
}

