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
    startAngle = 150;
    startSpeed();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initCanvas(QPainter& painter)
{
    painter.setRenderHint(QPainter::Antialiasing,true);

    //底色弄成黑色
    painter.setBrush(Qt::black);
    painter.drawRect(rect());

    //坐标系 平移到中心
    QPoint cent(rect().width()/2, rect().height()*0.6);
    painter.translate(cent);
}

void Widget::drawMiddleCircle(QPainter &painter, int radius)
{
    // 画小圆
    painter.setPen(QPen(Qt::white,3));
    painter.drawEllipse(QPoint(0,0),radius,radius);
}

void Widget::drawCurrentSpeed(QPainter &painter)
{
    //当前值
    painter.setPen(Qt::white);
    QFont font("Arial",30);
    font.setBold(true);
    painter.setFont(font);
    // painter.drawText(0,0,QString::number(currentValue));
    painter.drawText(QRect(-60,-60,120,70),Qt::AlignCenter,QString::number(currentValue));

    QFont font2("Arial",13);
    font.setBold(true);
    painter.setFont(font2);
    painter.drawText(QRect(-60,-60,120,160),Qt::AlignCenter,"Km/h");
}

void Widget::drawScale(QPainter &painter, int radius)
{
    //画刻度
    //1. 算出一个刻度需要旋转的角度
    angle = 240*1.0 / 60;//270*1.0的作用是扩大变量类型，把int型阔成double,保留小数
    //保存当前坐标位置，此时此刻是在原点，x在3点钟方向
    painter.save();
    painter.setPen(QPen(Qt::white,5));
    //2.  设置第一个刻度的位置
    painter.rotate(startAngle);
    for(int i=0;i<=60;i++){
        if( i >= 40){
            painter.setPen(QPen(Qt::red,5));
        }
        if(i % 5 == 0){
            //画长的刻度线
            painter.drawLine(radius - 20, 0, radius - 3 ,0);
        }else{//画短的刻度线
            painter.drawLine(radius - 8, 0, radius - 3 ,0);
        }
        //画完后旋转
        painter.rotate(angle);
    }
    painter.restore();
    painter.setPen(QPen(Qt::white,5));
}

void Widget::drawScaleText(QPainter &painter, int radius)
{
    //写刻度文字
    QFont font("Arial",15);
    font.setBold(true);
    painter.setFont(font);
    int r = radius - 49;
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
}

void Widget::drawPointLine(QPainter &painter,int lenth)
{
    //画指针，线
    //坐标轴先回到原点
    painter.restore();
    painter.save();


    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    static const QPointF points[4] = {
        QPointF(0,0.0),
        QPointF(200.0,-1.1),
        QPointF(200.0,1.1),
        QPointF(0,15.0),

    };


    painter.rotate(startAngle + angle * currentValue);
    painter.drawPolygon(points, 4);
    // painter.drawLine(60,0,lenth,0);

}

void Widget::drawSpeedPie(QPainter &painter, int radius)
{
    painter.restore();
    QRect rentangle(-radius,-radius,radius*2,radius*2);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255,0,0,80));
    painter.drawPie(rentangle,(360-startAngle)*16,-angle*currentValue*16);//angle前面取 负数，为了让它顺时针方向画
}

void Widget::startSpeed()
{
    timer = new QTimer(this);

    currentValue = 0;
    connect(timer, &QTimer::timeout,[=](){
        if(mark == 0){
            currentValue++;
            if(currentValue >= 61){
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

void Widget::drawEllipseInnerBlack(QPainter &painter, int radius)
{
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(0,0),radius,radius);
}

void Widget::drawEllipseInnerShine(QPainter &painter, int radius)
{
    QRadialGradient radialGradient(0,0,radius);
    radialGradient.setColorAt(0.0, QColor(255,0,0,200)); // 中心颜色
    radialGradient.setColorAt(1.0, QColor(0,0,0,100));  // 外围颜色
    painter.setBrush(radialGradient);
    painter.drawEllipse(QPoint(0,0),radius,radius);
}

void Widget::drawEllipseOutterShine(QPainter &painter, int radius)
{
    painter.restore();
    QRect rentangle(-radius,-radius,radius*2,radius*2);
    painter.setPen(Qt::NoPen);

    QRadialGradient radiaGradient(0,0,radius);
    radiaGradient.setColorAt(1,QColor(255,0,0,200));
    radiaGradient.setColorAt(0.97,QColor(255,0,0,120));
    radiaGradient.setColorAt(0.9,QColor(0,0,0,0));
    radiaGradient.setColorAt(0,QColor(0,0,0,0));
    painter.setBrush(radiaGradient);

    painter.drawPie(rentangle,(360-150)*16,-angle*61*16);//angle前面取 负数，为了让它顺时针方向画
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //初始化画布
    initCanvas(painter);
    //画小圆
    drawMiddleCircle(painter,60);
    //画刻度
    drawScale(painter, height()/2);
    //画刻度文字
    drawScaleText(painter, height()/2);
    //指针
    drawPointLine(painter, height()/2-58);
    //画扇形
    drawSpeedPie(painter, height()/2+25);
    //画渐变内圈圆
    drawEllipseInnerShine(painter,110);
    //画黑色内圈
    drawEllipseInnerBlack(painter, 80);
    //画当前速度
    drawCurrentSpeed(painter);
    //画外环发光圈
    drawEllipseOutterShine(painter, height()/2+25);
}

