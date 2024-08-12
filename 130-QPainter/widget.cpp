#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPainter>
#include <QTimer>

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
    QPen pen(Qt::red,7);
    painter.setPen(pen);
   // painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 20));
    painter.drawText(rect(), Qt::AlignCenter, "Qt的案例");

    //画线
   // painter.drawLine(10,200,300,20);
   // painter.drawLine(QLine(10,200,300,20));
    painter.drawLine(QPoint(10,200),QPoint(300,20));
    //画矩形
//    drawRect(const QRectF &rectangle)
                  //  左上角点的x坐标，y坐标，长，宽
    QRect rectangle(200,100,200,150);
    painter.drawRect(rectangle);   // x y,  Point  Qrect
//    drawRect(int x, int y, int width, int height)
   // painter.drawRect(200,100,200,100);
//    drawRect(const QRect &rectangle)
    //画圆形
    //painter.drawEllipse(rectangle);
    // painter.drawEllipse(rect().center(),200,100);
    // painter.drawEllipse(QPoint(80,500),80,80);

    // painter.drawArc(rectangle,-30*16,120*16);
     painter.drawArc(30,100,100,180,45*16,90*16);
    // painter.draw
     painter.drawPie(30,300,100,180,45*16,90*16);
}


void Widget::on_pushButton_clicked()
{


}
