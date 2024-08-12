#include <iostream>
#include <string>

using namespace std;

class PrintInt
{
private:
    int data;

public:
    void printIntData();
    void setIntData(int data);
};

void PrintInt::printIntData()
{
    cout << data << endl;
}
void PrintInt::setIntData(int data)
{
    this->data = data;
}

class PrintString
{
private:
    string data;

public:
    void printPrintData();
    void setStringData(string data);
};

void PrintString::printPrintData()
{
    cout << data << endl;
}

void PrintString::setStringData(string data)
{
    this->data = data;
}

template <typename T>
class PrintEveryThing
{
private:
    T data;

public:
    void printPrintData(){
        cout << data << endl;
    }
    void setStringData(T data){
        this->data = data;
    }
};


int main()
{
    PrintInt p1;
    p1.setIntData(10);
    p1.printIntData();

    PrintString p2;
    p2.setStringData("hello");
    p2.printPrintData();

    PrintEveryThing p3<int>;
    return 0;
}
