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

    void run(){
        cout << "����������" << endl;
    }
    void stop();
};

//�����࣬����
class Bickle : public Vehicle{

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
    Roadster ftype;
    ftype.type = "�ݱ�Ftype";
    ftype.run();
    Bickle bike;
    bike.type = "����";
    bike.run();
    return 0;
}
