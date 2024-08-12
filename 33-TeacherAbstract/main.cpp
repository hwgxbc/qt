
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
        cout << "英语老师开始进入教室" << endl;
    }
    void startTeaching() override{
        cout << "英语老师开始教学" << endl;
    }
    void afterTeaching() override{

    };
};

class ProTeacher : public Teacher{
public:
    void goInClass() override{
        cout << "编程老师开始进入教室" << endl;
    }
    void startTeaching() override{
        cout << "编程老师开始撸代码了，拒绝读PPT" << endl;
    }
    void afterTeaching() override{
        cout << "编程老师下课后手把手教x学员写代码" << endl;
    };
};

int main()
{
    // Teacher t;//抽象类，不支持被实例化
    EnglishTeacher e;
    e.goInClass();
    ProTeacher t;
    t.startTeaching();
    t.afterTeaching();
    //抽象类，多态
    Teacher *teacher = new ProTeacher;
    teacher->startTeaching();
    return 0;
}
