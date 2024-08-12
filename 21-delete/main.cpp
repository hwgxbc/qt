#include <iostream>

class MyClass {
public:
    MyClass() {
        std::cout << "Object created" << std::endl;
    }
};
int main() {
    // 分配单个对象
    MyClass* myObject = new MyClass();
    // 分配对象数组
    int* myArray = new int[5]{1, 2, 3, 4, 5};
    // 使用对象和数组...
    // 释放内存
    delete myObject;
    delete[] myArray;

    return 0;
}
