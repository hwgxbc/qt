
#include <iostream>

using namespace std;

class Myclass{

private:
    static int staticNumofInstance;

public:
    Myclass(){
        staticNumofInstance++;
    }

    ~Myclass(){
        staticNumofInstance--;
    }

    static int getNunofInstance(){
        return staticNumofInstance;
    }
};

int Myclass::staticNumofInstance = 0;

int main()
{
    Myclass m1;
    cout << Myclass::getNunofInstance() << endl;
    Myclass m2;
    cout << m2.getNunofInstance() << endl;

    {
        Myclass m3;
        cout << Myclass::getNunofInstance() << endl;
        Myclass m4;
        cout << Myclass::getNunofInstance() << endl;
    }
    cout << Myclass::getNunofInstance() << endl;
    Myclass *m5 = new Myclass;
    cout << Myclass::getNunofInstance() << endl;
    delete m5;
    cout << Myclass::getNunofInstance() << endl;
    return 0;
}
