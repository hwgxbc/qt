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
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 20));
    painter.drawText(rect(), Qt::AlignCenter, "Qt的案例");

//    void
//    drawText(int x, int y, const QString &text)
//    void
//    drawText(const QRectF &rectangle, int flags, const QString &text, QRectF *boundingRect = nullptr)
//    void
//    drawText(const QRect &rectangle, int flags, const QString &text, QRect *boundingRect = nullptr)
//    void
//    drawText(int x, int y, int width, int height, int flags, const QString &text, QRect *boundingRect = nullptr)
    painter.drawText(100,200,100,100,Qt::AlignCenter, "Qt");
    painter.drawText(10,30,"老陈甩");
    qDebug() << rect().width() << "," << rect().height();
}


void Widget::on_pushButton_clicked()
{


}
