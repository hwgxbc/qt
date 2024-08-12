#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QDebug>
#include <QTimer>
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
            if(currentValue >= 51){
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
    painter.translate(rect().center());
    QRadialGradient radialGradient(0, 0, height()/2); // 中心和半径 (50, 50, 50)
    // 设置颜色停靠点
    radialGradient.setColorAt(0.0, QColor(255,0,0,50)); // 中心颜色
    radialGradient.setColorAt(1.0, QColor(255,0,0,250));  // 外围颜色

    // 使用这个渐变创建 QBrush
    QBrush brush(radialGradient);
    painter.setBrush(brush);
    // 画大圆
    painter.drawEllipse(QPoint(0,0),height()/2,height()/2);
    painter.setBrush(Qt::NoBrush);
    // 画小圆
    painter.setPen(QPen(Qt::white,3));
    painter.drawEllipse(QPoint(0,0),60,60);

    //当前值
    painter.setFont(QFont("华文宋体",25));
   // painter.drawText(0,0,QString::number(currentValue));
    painter.drawText(QRect(-60,-60,120,120),Qt::AlignCenter,QString::number(currentValue));
    //画刻度
    //1. 算出一个刻度需要旋转的角度
    double angle = 270*1.0 / 50;//270*1.0的作用是扩大变量类型，把int型阔成double,保留小数
    //2.  设置第一个刻度的位置
    painter.setFont(QFont("华文宋体",15));
    painter.save();//保存当前坐标位置，此时此刻是在原点，x在3点钟方向
    painter.rotate(135);
    for(int i=0;i<=50;i++){
        if(i % 10 == 0){
            //画字
            if(135 + angle * i < 270){
                painter.rotate(180);
                painter.drawText(-(height()/2 - 20 - 10), 8,QString::number(i));
                painter.rotate(-180);
            }else{
                painter.drawText(height()/2 - 20 - 30, 8,QString::number(i));
            }

            //画长的刻度线
            painter.drawLine(height()/2 - 20, 0, height()/2 - 3 ,0);

        }else{//画短的刻度线
            painter.drawLine(height()/2 - 8, 0, height()/2 - 3 ,0);
        }
        //画完后旋转
        painter.rotate(angle);
    }
    //画指针，线
    //坐标轴先回到原点
    painter.restore();
    painter.save();
    painter.rotate(135 + angle * currentValue);
    painter.drawLine(60,0,height()/2 - 20- 10 - 28,0);

    //画扇形
    painter.restore();
    QRect rentangle(-height()/2+58,-height()/2+58,height()-116,height()-116);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(235,152,50,150));
    painter.drawPie(rentangle,(360-135)*16,-angle*currentValue*16);//angle前面取 负数，为了让它顺时针方向画
}

