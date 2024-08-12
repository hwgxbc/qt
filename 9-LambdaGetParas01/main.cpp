#include <iostream>

using namespace std;

int main() {

    int x = 10;
    int y = 20;

    auto add = [x,y]()->int{
        //x++;
        //x = 15;这种方式捕获，是不能修改变量值的，只用能用，可读
        return x + y;
    };

    int ret = add();
    cout << ret << endl;

    int z = 5;
    auto mul = [=]()->int{
        //x++;
        //x = 15;这种方式捕获所有变量，不需要去在列表中写明，是不能修改变量值的，只用能用，可读
        return x * y * z;
    };
    ret = mul();
    cout << ret << endl;

    //用引用的方式来捕获，引用类似指针，进行地址访问
    auto modifyAndMul = [&]()->int{
        //x++;
        x = 15; //引用的方式进行所有变量的捕获，可读可写
        return x * y * z;
    };
    ret = modifyAndMul();
    cout << ret << endl;
    cout << "x=" << x << endl;

    return 0;
}
