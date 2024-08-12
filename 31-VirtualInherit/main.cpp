
#include <iostream>

using namespace std;

class Base {
public:
     int data;
     Base(int data){
         this->data = data;
     }
     void printInfo()
     {
         cout << data << endl;
     }
};

class Derived1 : virtual public Base {
    // �̳��� Base
public:

    Derived1(int data) : Base(data){

    }
};

class Derived2 : virtual public Base {
    // �̳��� Base
public:

    Derived2(int data) : Base(data){

    }
};

class FinalDerived : public Derived1, public Derived2 {
    // �̳��� Derived1 �� Derived2
public:
    FinalDerived(int data) : Base(data),Derived1(data),Derived2(data){

    }
};

int main()
{
    FinalDerived final(10);
    final.printInfo();
    return 0;
}
