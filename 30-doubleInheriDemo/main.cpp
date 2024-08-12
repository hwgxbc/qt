#include <iostream>

using namespace std;

class ClassA {
public:
    void displayA() {
        std::cout << "Displaying ClassA" << std::endl;
    }
    void testFunc(){
         std::cout << "testFunc ClassA" << std::endl;
    }
};

class ClassB {
public:
    void displayB() {
        std::cout << "Displaying ClassB" << std::endl;
    }
    void testFunc(){
         std::cout << "testFunc ClassB" << std::endl;
    }
};

class Derived : public ClassA, public ClassB {
public:
    void display() {
        displayA(); // ���� ClassA �� displayA
        displayB(); // ���� ClassB �� displayB
        ClassA::testFunc();
    }
};

int main() {
    Derived obj;

    obj.displayA();  // ���� ClassA �� displayA
    obj.displayB();  // ���� ClassB �� displayB
    obj.display();   // ���� Derived �� display
    return 0;
}
