#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QRadialGradient radialGradient(width()/2,height()/2,200);
    radialGradient.setColorAt(0.1, Qt::red);
    radialGradient.setColorAt(1, Qt::yellow);
    painter.setBrush(QBrush(radialGradient));



//    QConicalGradient conicalGradient(210, 310, 0); // 中心点 (100, 100)，起始角度 0

//    // 添加颜色停靠点
//    conicalGradient.setColorAt(0.0, Qt::red);
//    conicalGradient.setColorAt(0.5, Qt::blue);
//    conicalGradient.setColorAt(1.0, Qt::red);

//    // 使用这个渐变创建 QBrush
//    QBrush brush(conicalGradient);

//    painter.setPen(Qt::NoPen); // 无边框
//    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
//     painter.drawRect(200,300,400,200);
    painter.drawPie(rect(),30*16,120*16);
}

