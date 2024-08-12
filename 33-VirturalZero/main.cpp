#include <iostream>

using namespace std;

class RemoteCon{
public:
    virtual void openUtils() = 0; //���麯��
};

class TvRemoteCon : public RemoteCon{

public:
    void openUtils() override{
        cout << "����ң�����Ŀ�������" << endl;
    }

    void testFunc(){

    }
};

class RoundspeakerCon : public RemoteCon{

public:
    void openUtils() override{
        cout << "����ң�����Ŀ�������" << endl;
    }
};

class LightCon : public RemoteCon{

public:
    void openUtils() override{
        cout << "�ƹ�ң�����Ŀ�������" << endl;
    }
};

void test(RemoteCon& r)
{
    r.openUtils();
}

int main()
{
    //absctract class �����࣬���ܱ�ʵ�����ġ�
    //RemoteCon c;
    //c.openUtils();

    RemoteCon *remoteCon = new TvRemoteCon; //��̬
    remoteCon->openUtils();

    RemoteCon *remoteCon2 = new RoundspeakerCon; //��̬
    remoteCon2->openUtils();

    RemoteCon *remoteCon3 = new LightCon; //��̬
    remoteCon3->openUtils();

    TvRemoteCon tvRemote;
    test(tvRemote);

    return 0;
}
