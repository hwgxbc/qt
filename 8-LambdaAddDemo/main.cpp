#include <iostream>

using namespace std;

/*
 *
 * [capture clause](parameters) -> return_type {
    // 函数体
    // 可以使用捕获列表中的变量
    return expression; // 可选的返回语句
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
