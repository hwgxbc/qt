#include <stdio.h>

struct Vehicle{ //��ͨ���ߣ���,����ĸ���

    char *type;
    char *contry;
    char *color;
    double price;
    int numOfWheel;

    void (*prun)();
    void (*pstop)();
};

struct Roadster{ //�ܳ���Ҳ�ǳ��󣬱ȸ���о��Ϸ�Χ��С�˵�

    struct Vehicle baseMes;

    void (*openTopped)();
    void (*pdrifting)();
};

int main()
{
    struct Roadster ftype;//���󣬾۽�������ݱ���ftype
    return 0;
}
