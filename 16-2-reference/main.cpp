#include <iostream>

using namespace std;
/*
void swap(int a, int b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
    cout << "�����" << endl;
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

    cout << "����֮ǰ��" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    swap(a,b);
    cout << "����֮��"<< endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    return 0;
}
