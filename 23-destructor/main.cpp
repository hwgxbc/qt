#include <iostream>

using namespace std;


class MyClass{

private:
    int* datas;

public:
    MyClass(int size){
        datas = new int[size];
    }

    ~MyClass(){
        cout << "��������������" << endl;
        delete[] datas;
    }
};

int main()
{

    MyClass m1(5);
    MyClass *m2 = new MyClass(10);


    delete m2;
    return 0;
}
