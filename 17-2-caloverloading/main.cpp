#include <iostream>

using namespace std;


class Person
{
public:
    string name;
    int inNumberTail;

    bool operator==(Person pTmp);

};
bool Person::operator==(Person pTmp){

    return pTmp.name == name && pTmp.inNumberTail == inNumberTail;
}

int main()
{
    //假设我们认定名字和身份证尾号6位一样的两个对象是同一个人！
    Person p1;
    p1.name = "张三";
    p1.inNumberTail = 412508;

    Person p2;
    p2.name = "张三";
    p2.inNumberTail = 412508;

    bool ret = p1 == p2;
    cout << ret << endl;

    return 0;
}
