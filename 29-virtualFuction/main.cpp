#include <iostream>
using namespace std;

//���࣬����
class Vehicle{ //��ͨ���ߣ���,����ĸ���
public:
    string contry;
    double price;

    Vehicle(){};
    virtual ~Vehicle(){};
    Vehicle(string contry, double price){

        this->contry = contry;
        this->price = price;
    };

    //������������һ���麯��
    virtual void run(){
        cout << "����������" << endl;
    }
    virtual void stop();
};

class Bike : public Vehicle{

public:
    void run() override {
        cout << "�Ų����г�" << endl;
    }
};

int main()
{

    Bike b;
    b.run();
    return 0;
}
