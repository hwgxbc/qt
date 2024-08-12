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
        displayA(); // 调用 ClassA 的 displayA
        displayB(); // 调用 ClassB 的 displayB
        ClassA::testFunc();
    }
};

int main() {
    Derived obj;

    obj.displayA();  // 调用 ClassA 的 displayA
    obj.displayB();  // 调用 ClassB 的 displayB
    obj.display();   // 调用 Derived 的 display
    return 0;
}
