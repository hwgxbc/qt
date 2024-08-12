#include <iostream>

using namespace std;

class Car {
public:
    string brand;  // 不需要使用std::string
    string type;
    int year;

    Car(string b, string t, int y):brand(b),type(t),year(y){
        cout << "参数列表的方式进行构造" << endl;
    }
    Car(){
        cout << "构造函数被调用" << endl;
    }
    Car(string b, int y){
        cout << "带参数的构造函数被调用" << endl;
        brand = b;
        year = y;
    }
    Car(string b){
        cout << "带一个参数的构造函数被调用" << endl;
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
    car.brand = "宝马";
    car.year = 2023;
    car.display();

    Car car2("比亚迪");
    car2.year = 2023;
    car2.display();

    Car car3("奇瑞","风云2",2014);
    car3.displayAll();

    Car *pcar = new Car("捷豹",2024);
    pcar->display();

    delete pcar;

    return 0;
}
