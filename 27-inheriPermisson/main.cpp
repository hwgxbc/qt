#include <iostream>
using namespace std;

//���࣬����
class Vehicle{ //��ͨ���ߣ���,����ĸ���
public:
    string type;
    string contry;
    string color;
    double price;
    int numOfWheel;
protected:
    int protectedData;
private:
    int privateData;

public:
    void run(){
        cout << "����������" << endl;
    }
    void stop();
};

//˽�м̳в���
class TestClass : private Vehicle{
public:
    void tsetFunc(){
        price = 10; //����Ĺ������ݱ�˽�м̳к�����������Ȩ�ޱ��˽�У�ֻ�������ڲ�ʹ��
    }
};
//���м̳в���
class Truck : protected Vehicle{

public:
    void testFunc(){
        type = "���ݲ���"; //����˹���Ȩ��
        protectedData = 10; //���ֹ���Ȩ��
        privateData = 10; //�����ˣ������˽�г�Ա���������ַ�ʽ�ļ̳ж��ǲ��ɷ��ʵġ�
    }
};

//���м̳У�����Ĺ���Ȩ�޺ͱ���Ȩ�޲��䣬˽�г�Ա���ܷ���
class Bickle : public Vehicle{

public:
    void testFunc(){
        protectedData = 10;
    }
};

//�����࣬����
class Roadster : public Vehicle{ //�ܳ���Ҳ�ǳ��󣬱ȸ���о��Ϸ�Χ��С�˵�
public:
    int stateOfTop;

    void openTopped();
    void pdrifting();
};

int main()
{
    TestClass test;
    test.price = 3.3; //�����ˣ�����Ĺ��г�Ա��˽�м̳к󣬽�Ϊ˽��Ȩ��

    Truck t;
    t.type = "����"; //�����ˣ�����Ĺ��г�Ա�������̳к󣬽�Ϊ����Ȩ��
    t.protectedData = 10; //�ӱ�����Ϣ�����������̳���ɻ���ı�����Ա���Ǳ��ֱ���Ȩ��
    Roadster ftype;
    ftype.type = "�ݱ�Ftype";
    ftype.run();
    Bickle bike;
    bike.type = "����";
    bike.run();
    return 0;
}
