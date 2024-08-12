
#include <iostream>

using namespace std;

class QWidget{
public:

    QWidget(QWidget *parent){
        cout<<"组件初始化"<<endl;
    }
};

class Ui{
public:
    int *a;
};


class Widget : public QWidget{
public:
    Widget(QWidget *parent);

private:
    Ui *ui;
};

//Widget::Widget(QWidget *parent) : QWidget(parent),ui(new Ui::Widget)
Widget::Widget(QWidget *parent) : QWidget(parent),ui(new Ui)
{

}

int main()
{

    return 0;
}
