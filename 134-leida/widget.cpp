#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,[=](){
        //不断变化扇形的启动位置
        startAngle += 30;
        if(startAngle >= 360){
            startAngle = 0;
        }
       update();
    });

    timer->setInterval(100);
    timer->start();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 抗锯齿
    painter.setRenderHint(QPainter::Antialiasing,true);
    // 把背景色刷成黑色
    QBrush brush(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(rect());

    // 平移坐标轴到窗口正中间
    painter.translate(rect().center());

    // 最小圆的半径
    int rEve = height()/2/7; //800 600   600/7
    int dataTmp = rEve * 7; //用height()/2 导致突出，上面那行代码除不尽

    // 设置画笔，绿色，像素4
    QPen pen(Qt::green,4);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); //不要画刷，否则只能看到最外面的圈
    for(int i=1; i <= 7; i++){
        painter.drawEllipse(QPoint(0,0),rEve*i,rEve*i); //依次画出7个圆形
    }

    painter.drawLine(-rEve*7,0,rEve*7,0);
    painter.drawLine(0,-rEve*7,0,rEve*7);

    //设置锥形渐变
    QConicalGradient conGradient(0,0,-startAngle);
    conGradient.setColorAt(0,QColor(0,255,0,200));
    conGradient.setColorAt(0.1,QColor(0,255,0,100));
    conGradient.setColorAt(0.2,QColor(0,255,0,0));
    conGradient.setColorAt(1,QColor(0,255,0,0));
    //直接用渐变色指定画刷
    painter.setBrush(conGradient);
    painter.setPen(Qt::NoPen); //去除扇形区域边框
    //画出扇形，启动角度是startAngle,由定时器来修改
    painter.drawPie(QRect(-dataTmp,-dataTmp,dataTmp*2,dataTmp*2),
                    -startAngle*16,70*16);
}

