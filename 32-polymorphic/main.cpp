#include <iostream>

using namespace std;

class RemoteCon{
public:
    virtual void openUtils(){ //虚函数
        cout << "遥控器的开被按下" << endl;
    }
};

class TvRemoteCon : public RemoteCon{

public:
    void openUtils() override{
        cout << "电视遥控器的开被按下" << endl;
    }

    void testFunc(){

    }
};

class RoundspeakerCon : public RemoteCon{

public:
    void openUtils() override{
        cout << "音响遥控器的开被按下" << endl;
    }
};

class LightCon : public RemoteCon{

public:
    void openUtils() override{
        cout << "灯光遥控器的开被按下" << endl;
    }
};

void test(RemoteCon& r)
{
    r.openUtils();
}

int main()
{

    RemoteCon c;
    c.openUtils();

    RemoteCon *remoteCon = new TvRemoteCon; //多态
    remoteCon->openUtils();

    RemoteCon *remoteCon2 = new RoundspeakerCon; //多态
    remoteCon2->openUtils();

    RemoteCon *remoteCon3 = new LightCon; //多态
    remoteCon3->openUtils();

    TvRemoteCon tvRemote;
    test(tvRemote);

    return 0;
}
