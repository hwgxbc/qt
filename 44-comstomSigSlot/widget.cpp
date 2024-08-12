#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(this,SIGNAL(mysignal()),this,SLOT(myslot()));
    connect(this,SIGNAL(mysignalparams(int)),this,SLOT(myslotparams(int)));
    emit mysignal();
    emit mysignalparams(100);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::myslot()
{
    std::cout << "myslot" << std::endl;
}

void Widget::myslotparams(int value)
{
    qDebug() << "myslotparams";
    qDebug() << value ;
}

