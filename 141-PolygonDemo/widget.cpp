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
    painter.setBrush(Qt::red);
    painter.translate(rect().center());
    static const QPointF points[3] = {
        QPointF(-10.0, 0),
        QPointF(0, -200.0),
        QPointF(10.0, 0),

    };

    painter.drawPolygon(points, 4);
}

