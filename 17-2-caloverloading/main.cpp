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
    //���������϶����ֺ����֤β��6λһ��������������ͬһ���ˣ�
    Person p1;
    p1.name = "����";
    p1.inNumberTail = 412508;

    Person p2;
    p2.name = "����";
    p2.inNumberTail = 412508;

    bool ret = p1 == p2;
    cout << ret << endl;

    return 0;
}
