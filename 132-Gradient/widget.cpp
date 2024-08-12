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
    QLinearGradient lineGradient(width()/2,0,width()/2,height());
    lineGradient.setColorAt(0.1,QColor(0,0,0,255));
    lineGradient.setColorAt(0.3,QColor(0,0,0,180));
    lineGradient.setColorAt(0.5,QColor(0,0,0,100));
    lineGradient.setColorAt(1,Qt::white);

    QBrush brush(lineGradient);
    painter.setBrush(brush);
    painter.drawRect(rect());

}

