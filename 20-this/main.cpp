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
        //        cout << "���캯���У�" << endl;
        //        cout << this << endl;
    }

    void display() const {
        cout << "Brand: " << this->brand << ", Year: " << this->year << endl;
        // Ҳ���Բ�ʹ�� this->��ֱ��д brand �� year
    }

    Car& setYear(int year) {
        this->year = year; // �������
        return *this; // ���ص��ö��������
    }
};

int main()
{
    Car car("����",2024);
    car.display();

    // ��ʽ����
    car.setYear(2023).display();

    //    cout << "main�����У�" << endl;
    //    cout << &car << endl;

    //    Car car2("����",2024);
    //    cout << "main�����У�" << endl;
    //    cout << &car2 << endl;
    return 0;
}
