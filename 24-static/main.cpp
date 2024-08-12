#include <iostream>

using namespace std;

class Test{
public:
    void printInfo();
};

class Myclass{

public:
    int datas;
    static int staticValue;

    void printInfo(){
        cout << datas << endl;
    }
    static int getStaticValue(){

        return staticValue;
    }
};

void Test::printInfo(){
   Myclass::staticValue++;
   cout << "test¶ÔÏó´òÓ¡"<<endl;
   cout << Myclass::getStaticValue() << endl;
}

int Myclass::staticValue = 0;

int main()
{
    Test t;
    t.printInfo();
    cout << Myclass::staticValue << endl;
    cout << Myclass::getStaticValue() << endl;
    return 0;
}
