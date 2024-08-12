#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,[=](){
        //update();
        repaint();
    });
    timer->setInterval(1000);
    timer->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    static int i = 0;
    qDebug() << "painterEvent" << i++;
}


void Widget::on_pushButton_clicked()
{
    update();

}
