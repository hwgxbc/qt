#include <iostream>

class MyClass {
public:
    MyClass() {
        std::cout << "Object created" << std::endl;
    }
};
int main() {
    // ���䵥������
    MyClass* myObject = new MyClass();
    // �����������
    int* myArray = new int[5]{1, 2, 3, 4, 5};
    // ʹ�ö��������...
    // �ͷ��ڴ�
    delete myObject;
    delete[] myArray;

    return 0;
}
