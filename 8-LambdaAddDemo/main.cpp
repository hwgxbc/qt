#include <iostream>

using namespace std;

/*
 *
 * [capture clause](parameters) -> return_type {
    // ������
    // ����ʹ�ò����б��еı���
    return expression; // ��ѡ�ķ������
    }
int add(int a, int b)
{
    return a + b;
}
*/

int main()
{
    int x = 50;
    int y = 20;

    auto add = [](int a, int b)->int{
        return a + b;
    };

    int ret = add(x,y);

    cout << ret;
    return 0;
}
