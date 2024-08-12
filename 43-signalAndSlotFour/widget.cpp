#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //在构造函数中进行信号与槽的绑定
    //第二种方式：QObject::connect(sender, SIGNAL(signal()), receiver, SLOT(slot()));
    QObject::connect(ui->btnCon, SIGNAL(clicked()), this, SLOT(on_btnCon_clickedMyself()));

    //第三方式：lambda表达式：QObject::connect(sender, &Sender::signal, [=]() { /* lambda body */ });
    QObject::connect(ui->btnLambda, &QPushButton::clicked,[=](){
        std::cout << "btnLambdaClicked" << std::endl;
    });
    //第四种方式：QObject::connect(sender, &Sender::signal, receiver, &Receiver::slot);
    QObject::connect(ui->btnFortch,&QPushButton::clicked,this,&Widget::on_fortch_clicked);
}

Widget::~Widget()
{
    delete ui;
}

//第一种方式：通过uiDesigner
void Widget::on_btnui_clicked()
{
    std::cout << "UIBtnClicked" << std::endl;
}

void Widget::on_btnCon_clickedMyself()
{
    std::cout << "btnConClicked" << std::endl;
}

void Widget::on_fortch_clicked()
{
    std::cout << "btnForthClicked" << std::endl;
}
