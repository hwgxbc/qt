#include <iostream>

using namespace std;

int main()
{
    int a = 0;
    int b = 0;
    bool dataBool = false;
    if(true)
    cout << "你好，世界，我是C++" << endl;

    cout << "你好，世界，我是C++" << "你好，我是补充输出的"<< endl;
    cin >> a;
    cin >> b;
    cout << a <<"," << b << endl;
    cout << a <<"+" << b << "=" << a+b << endl;
    cerr << "程序错误退出" << endl;

    std::cout << "The range of int is from " << INT_MIN << " to " << INT_MAX << std::endl;
    std::cout << "The maximum value of unsigned int is " << UINT_MAX << std::endl;
    std::cout << "The range of long long is from " << LLONG_MIN << " to " << LLONG_MAX << std::endl;
    return 0;
}
