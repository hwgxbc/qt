#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QtMath>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);

    currentValue = 0;
    connect(timer, &QTimer::timeout,[=](){
        if(mark == 0){
            currentValue++;
            if(currentValue >= 60){
                mark = 1;
            }

        }
        if(mark == 1){
            currentValue--;
            if(currentValue == 0){
                mark = 0;
            }
        }

        update();
    });
    timer->start(50);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    //底色弄成黑色
    painter.setBrush(Qt::black);
    painter.drawRect(rect());

    //坐标系 平移到中心
    QPoint cent(rect().width()/2, rect().height()*0.6);
    painter.translate(cent);

    // 画大圆
    painter.drawEllipse(QPoint(0,0),height()/2,height()/2);
    painter.setBrush(Qt::NoBrush);
    // 画小圆
    painter.setPen(QPen(Qt::white,3));
    painter.drawEllipse(QPoint(0,0),60,60);

    //当前值
    painter.setFont(QFont("华文宋体",20));
    // painter.drawText(0,0,QString::number(currentValue));
    painter.drawText(QRect(-60,-60,120,120),Qt::AlignCenter,QString::number(currentValue));
    //画刻度
    //1. 算出一个刻度需要旋转的角度
    double angle = 240*1.0 / 60;//270*1.0的作用是扩大变量类型，把int型阔成double,保留小数
    //2.  设置第一个刻度的位置

    painter.save();//保存当前坐标位置，此时此刻是在原点，x在3点钟方向
    painter.setPen(QPen(Qt::white,5));
    painter.rotate(150);
    for(int i=0;i<=60;i++){
        if(i % 5 == 0){
            //画长的刻度线

            painter.drawLine(height()/2 - 20, 0, height()/2 - 3 ,0);

        }else{//画短的刻度线
            painter.drawLine(height()/2 - 8, 0, height()/2 - 3 ,0);
        }
        //画完后旋转
        painter.rotate(angle);
    }
    painter.restore();
    //写刻度文字
    painter.setFont(QFont("华文宋体",18));
    int r = height()/2 - 46;
    for(int i=0; i<=60; i++){
        if(i % 5 == 0){
            //保存坐标系
            painter.save();
            //算出平移点，弧度=角度*3.1415/180
            int delX = qCos( (210-angle*i)*M_PI/180) * r;//QT中sin认的是弧度
            int delY = qSin(qDegreesToRadians(210-angle*i)) * r;
            //平移坐标系
            painter.translate(QPoint(delX,-delY));
            //旋转坐标系
            painter.rotate(-120+angle*i);//angle=4,30*4=120的时候，实参是0，120
            //写上文字
            painter.drawText(-25,-25,50,30,Qt::AlignCenter,QString::number(i*4));
            //恢复坐标系
            painter.restore();
        }
    }
    //画指针，线
    //坐标轴先回到原点
    painter.restore();
    painter.save();
    painter.rotate(150 + angle * currentValue);
    painter.drawLine(60,0,height()/2 - 20- 10 - 28,0);

    //画扇形
    painter.restore();
    QRect rentangle(-height()/2,-height()/2,height(),height());
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(235,152,50,150));
    painter.drawPie(rentangle,(360-150)*16,-angle*currentValue*16);//angle前面取 负数，为了让它顺时针方向画
}

