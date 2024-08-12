#include "widget.h"
#include "ui_widget.h"

#include <QTcpSocket>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    server = new QTcpServer(this);
    //bool QTcpServer::listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 0) 8888--15000
    QHostAddress addr("192.168.1.9");
    if(!server->listen(addr,8888)){
        qDebug() << "listenError";
        return;
    }

    connect(server,SIGNAL(newConnection()),this,SLOT(on_newClient_connect()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_newClient_connect()
{
    qDebug() << "newClient In!";
    //bool QTcpServer::hasPendingConnections() const
    if(server->hasPendingConnections()){
        //QTcpSocket *QTcpServer::nextPendingConnection()
        QTcpSocket *connction = server->nextPendingConnection();
        qDebug() << "client Addr: " << connction->peerAddress().toString() << "port:" << connction->peerPort();
    }
}

