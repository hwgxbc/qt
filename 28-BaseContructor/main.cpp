#include <iostream>
using namespace std;

//���࣬����
class Vehicle{ //��ͨ���ߣ���,����ĸ���
public:
    string contry;
    double price;

    Vehicle(string contry, double price){
        cout << "����Ĺ��캯��������" << endl;
        this->contry = contry;
        this->price = price;
    };

    void run(){
        cout << "����������" << endl;
    }
    void stop();
};


//�����࣬����
class Roadster : public Vehicle{ //�ܳ���Ҳ�ǳ��󣬱ȸ���о��Ϸ�Χ��С�˵�
public:
    int stateOfTop;
    Roadster(string contry, double price, int state) : Vehicle(contry, price){
        cout << "������Ĺ��캯��������" << endl;
        stateOfTop = state;
    }

    void openTopped();
    void pdrifting();
};

int main()
{

    Roadster FTYPE("����",70,0);
    return 0;
}
