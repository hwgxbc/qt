#include <stdio.h>

struct Vehicle{ //交通工具，车,抽象的概念

    char *type;
    char *contry;
    char *color;
    double price;
    int numOfWheel;

    void (*prun)();
    void (*pstop)();
};

struct Roadster{ //跑车，也是抽象，比父类感觉上范围缩小了点

    struct Vehicle baseMes;

    void (*openTopped)();
    void (*pdrifting)();
};

int main()
{
    struct Roadster ftype;//具象，聚焦到具体捷豹的ftype
    return 0;
}
