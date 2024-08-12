#include "widget.h"
#include "ui_widget.h"

#include <QMouseEvent>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFont(QFont("Arial",15));
    setFixedSize(507,936);
    setWindowFlag(Qt::FramelessWindowHint);
    //新建一个菜单组件
    menuQuit = new QMenu(this);
    //设置菜单项文字颜色
    menuQuit->setStyleSheet("QMenu::item {color:white}");
    //为菜单组件添加一个动作
    QAction *closeAct = new QAction(QIcon(":/res/close.png"), tr("退出"), this);
    menuQuit->addAction(closeAct);
    //用户选择菜单项并点击后回调函数，退出程序
    connect(menuQuit,&QMenu::triggered,this,[=]{
          this->close();
    });
    //由QNetworkAccessManager发起get请求
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl urlItBoy("http://t.weather.itboy.net/api/weather/city/101010100");
    QUrl urlTianQi("http://v1.yiketianqi.com/api?unescape=1&version=v61&appid=26371314&appsecret=qOhoD413");
    //指定请求的url地址
    QNetworkRequest res(urlItBoy);
    reply =  manager->get(res);
    //QNetworkRequest网络请求后进行数据读取
    connect(reply,&QNetworkReply::finished,this,&Widget::readHttpRply);
}
/*
QNetworkAccessManager *manager = new QNetworkAccessManager(this);
 connect(manager, &QNetworkAccessManager::finished,
         this, &MyClass::replyFinished);

 manager->get(QNetworkRequest(QUrl("http://qt-project.org")));*/

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        menuQuit->exec(QCursor::pos());
    }
    //鼠标当前位置 event->globalPos();，
    //窗口当前位置 this->pos()窗口新位置event->globalPos() - mOffset
    if(event->button() == Qt::LeftButton){
        mOffset = event->globalPos()-this->pos();
    }
}
//鼠标左键按下后的移动，导致这个事件被调用，设置窗口的新位置
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - mOffset);
}

void Widget::readHttpRply()
{
    //大多数服务器返回的字符编码格式是utf-8
    QByteArray data = reply->readAll();
    qDebug() << QString::fromUtf8(data);
}

