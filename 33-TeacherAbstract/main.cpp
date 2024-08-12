
#include <iostream>

using namespace std;

class Teacher{

public:
    string name;
    string shool;
    string major;

    virtual void goInClass() = 0;
    virtual void startTeaching() = 0;
    virtual void afterTeaching() = 0;
};

class EnglishTeacher : public Teacher{

public:
    void goInClass() override{
        cout << "Ӣ����ʦ��ʼ�������" << endl;
    }
    void startTeaching() override{
        cout << "Ӣ����ʦ��ʼ��ѧ" << endl;
    }
    void afterTeaching() override{

    };
};

class ProTeacher : public Teacher{
public:
    void goInClass() override{
        cout << "�����ʦ��ʼ�������" << endl;
    }
    void startTeaching() override{
        cout << "�����ʦ��ʼߣ�����ˣ��ܾ���PPT" << endl;
    }
    void afterTeaching() override{
        cout << "�����ʦ�¿κ��ְ��ֽ�xѧԱд����" << endl;
    };
};

int main()
{
    // Teacher t;//�����࣬��֧�ֱ�ʵ����
    EnglishTeacher e;
    e.goInClass();
    ProTeacher t;
    t.startTeaching();
    t.afterTeaching();
    //�����࣬��̬
    Teacher *teacher = new ProTeacher;
    teacher->startTeaching();
    return 0;
}
