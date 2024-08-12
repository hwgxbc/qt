#include "mybutton.h"

#include <QPainter>

MyButton::MyButton(QWidget *parent) : QWidget(parent)
{
    pic.load(":/o1.png");
    setFixedSize(pic.size());
    update();
}

void MyButton::mousePressEvent(QMouseEvent *event)
{
    pic.load(":/o3.png");
    update();
    emit clicked();
}

void MyButton::leaveEvent(QEvent *event)
{
    pic.load(":/o1.png");
    update();
}

void MyButton::enterEvent(QEvent *event)
{
    pic.load(":/o2.png");
    update();
}

void MyButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),pic);
}
