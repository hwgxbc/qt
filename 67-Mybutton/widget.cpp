#include "widget.h"
#include "ui_widget.h"
#include "mybutton.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->mybtn,&MyButton::clicked,[=](){
        qDebug() << "myButton is clicked !";
    });
}

Widget::~Widget()
{
    delete ui;
}

