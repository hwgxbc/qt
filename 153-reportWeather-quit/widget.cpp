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
        //qDebug() << "left Mouse clicked!";
        menuQuit->exec(QCursor::pos());
    }
}

