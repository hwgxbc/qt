#include <iostream>

using namespace std;
/*
void swap(int a, int b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
    cout << "函数里：" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

void swap(int *pa, int *pb)
{
    int tmp;
    tmp = *pa;
    *pa = *pb;
    b = tmp;
}*/

void swap(int& a, int& b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}


int main()
{
    int a = 10;
    int b = 20;

    cout << "交换之前：" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    swap(a,b);
    cout << "交换之后："<< endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    return 0;
}
