#include "widget.h"
#include "ui_widget.h"

#include <QTcpSocket>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    server = new QTcpServer(this);


    connect(server,SIGNAL(newConnection()),this,SLOT(on_newClient_connect()));
    ui->btnLineout->setEnabled(false);
    ui->btnStopListen->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_newClient_connect()
{

    //bool QTcpServer::hasPendingConnections() const
    if(server->hasPendingConnections()){
        //QTcpSocket *QTcpServer::nextPendingConnection()
        QTcpSocket *connction = server->nextPendingConnection();
        qDebug() << "client Addr: " << connction->peerAddress().toString() << "port:" << connction->peerPort();
        ui->textEditRev->insertPlainText("客户端地址:"+connction->peerAddress().toString()+
                                         "客户端端口号："+QString::number(connction->peerPort()) );
    }
}


void Widget::on_btnListen_clicked()
{
    //bool QTcpServer::listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 0) 8888--15000
    //QHostAddress addr("192.168.1.9");
    int port = ui->lineEditPort->text().toInt();
    if(!server->listen(QHostAddress::Any,port)){
        qDebug() << "listenError";
        return;
    }
    ui->btnListen->setEnabled(false);
    ui->btnLineout->setEnabled(true);
    ui->btnStopListen->setEnabled(true);
}
