#include <iostream>

using namespace std;

class Car {
public:
    string brand;  // ����Ҫʹ��std::string
    string type;
    int year;

    Car(string b, string t, int y):brand(b),type(t),year(y){
        cout << "�����б�ķ�ʽ���й���" << endl;
    }
    Car(){
        cout << "���캯��������" << endl;
    }
    Car(string b, int y){
        cout << "�������Ĺ��캯��������" << endl;
        brand = b;
        year = y;
    }
    Car(string b){
        cout << "��һ�������Ĺ��캯��������" << endl;
        brand = b;
    }

    void display() {
        cout << "Brand: " << brand << ", Year: " << year << endl;
    }
    void displayAll() {
        cout << "Brand: " << brand << ", Year: " << year << ",Type: " << type << endl;
    }

};

int main()
{
    Car car;
    car.brand = "����";
    car.year = 2023;
    car.display();

    Car car2("���ǵ�");
    car2.year = 2023;
    car2.display();

    Car car3("����","����2",2014);
    car3.displayAll();

    Car *pcar = new Car("�ݱ�",2024);
    pcar->display();

    delete pcar;

    return 0;
}
