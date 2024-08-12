#include <iostream>

using namespace std;

/*
int add(int a, int b)
{
    return a+b;
}

int minu(int a, int b)
{
    return a-b;
}

int mul(int a, int b)
{
    return a*b;
}

double diliv(int a, int b)
{
    return (double)a/b;
}
*/

int calculator(int a, int b, int (*p)(int a, int b))
{
    cout << "开始计算" << endl;
   // p(a,b);
}

int main()
{
    int a = 0;
    int b = 0;
    char cal;

    while(1){
        cout << "请输入两个数：" << endl;
        cin >> a;
        cin >> b;
        cout << "请输入运算符+，-，*，/" << endl;
        cin >> cal;
       // auto minu = [a,b]()->int{ return a - b;};
        switch(cal){
        case '+':
            cout << calculator(a,b,[](int a, int b){return a + b;}) << endl;
            break;
        case '-':
            cout << calculator(a,b,[](int a, int b){return a - b;}) << endl;
            break;
        case '*':
            cout << calculator(a,b,[](int a, int b){return a * b;}) << endl;
            break;
        case '/':
            cout << calculator(a,b,[](int a, int b){return a / b;}) << endl;
            break;
        }
    }

    //  cout << "Hello World!" << endl;
    return 0;
}
