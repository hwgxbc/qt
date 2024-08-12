#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    string brand;
    int year;

public:
    Car(string brand, int year) {
        this->brand = brand;
        this->year = year;
        //        cout << "构造函数中：" << endl;
        //        cout << this << endl;
    }

    void display() const {
        cout << "Brand: " << this->brand << ", Year: " << this->year << endl;
        // 也可以不使用 this->，直接写 brand 和 year
    }

    Car& setYear(int year) {
        this->year = year; // 更新年份
        return *this; // 返回调用对象的引用
    }
};

int main()
{
    Car car("宝马",2024);
    car.display();

    // 链式调用
    car.setYear(2023).display();

    //    cout << "main函数中：" << endl;
    //    cout << &car << endl;

    //    Car car2("宝马",2024);
    //    cout << "main函数中：" << endl;
    //    cout << &car2 << endl;
    return 0;
}
