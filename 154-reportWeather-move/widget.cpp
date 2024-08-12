#include "widget.h"
#include "ui_widget.h"

#include <QMouseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFont(QFont("Arial",15));
    setFixedSize(507,936);
    setWindowFlag(Qt::FramelessWindowHint);

    menuQuit = new QMenu(this);

    QAction *closeAct = new QAction(QIcon(":/res/close.png"), tr("退出"), this);
    menuQuit->addAction(closeAct);
    connect(menuQuit,&QMenu::triggered,this,[=]{
          this->close();
    });
     qDebug() << this->pos();
}
/*
 QMenu menu;
 QAction *at = actions[0]; // Assumes actions is not empty
 foreach (QAction *a, actions)
     menu.addAction(a);
 menu.exec(pos, at);
*/
Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        //qDebug() << "right Mouse clicked!";
        menuQuit->exec(QCursor::pos());
    }
    //鼠标当前位置 event->globalPos();，
    //窗口当前位置 this->pos()窗口新位置event->globalPos() - mOffset
    if(event->button() == Qt::LeftButton){
       // qDebug() << event->globalPos() << this->pos();
        mOffset = event->globalPos()-this->pos();
    }
}
//鼠标左键按下后的移动，导致这个事件被调用，设置窗口的新位置
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - mOffset);
}

