#include <stdio.h>
#include <stdlib.h>

struct Car{       //�������ࡱ
    char *color;  //��ɫ
    char *brand;  //Ʒ��
    char *type;   //����
    int year;     //����

    void (*printCarInfo)(char *color,char *brand,char *type, int year); //����ָ�룬ָ�򳵽��ܺ���
    void (*carRun)(char *type);       //����ָ�룬ָ�����еĺ���
    void (*carStop)(char *type);      //����ָ�룬ִ�г�ֹͣ�ĺ���
};

void bwmThreePrintCarInfo(char *color,char *brand,char *type, int year)
{
    printf("����Ʒ���ǣ�%s, �ͺ���: %s, ��ɫ�ǣ�%s,����������%d\n",
           brand,type,color,year);
}
void A6PrintCarInfo(char *color,char *brand,char *type, int year)
{
    printf("����Ʒ���ǣ�%s,�ͺ���: %s, ��ɫ�ǣ�%s, ����������%d\n",
           brand,type,color,year);
}

int main()
{
    struct Car BWMthree;
    BWMthree.color = "��ɫ";
    BWMthree.brand = "����";
    BWMthree.type  = "3ϵ";
    BWMthree.year  = 2023;

    BWMthree.printCarInfo = bwmThreePrintCarInfo;
    BWMthree.printCarInfo(BWMthree.color,BWMthree.brand,BWMthree.type,BWMthree.year);

    struct Car *AodiA6;
    AodiA6 = (struct Car*)malloc(sizeof(struct Car));

    AodiA6->color = "��ɫ";
    AodiA6->brand = "�µ�";
    AodiA6->type = "A6";
    AodiA6->year = 2008;

    AodiA6->printCarInfo = A6PrintCarInfo;
    AodiA6->printCarInfo(AodiA6->color,AodiA6->brand,AodiA6->type,AodiA6->year);
    return 0;
}
