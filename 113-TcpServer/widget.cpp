#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>
#include <QNetworkInterface>
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

    //QList<QHostAddress> QNetworkInterface::allAddresses()
    QList<QHostAddress> addresss = QNetworkInterface::allAddresses();
    for(QHostAddress tmp : addresss){
        if(tmp.protocol() == QAbstractSocket::IPv4Protocol){
            ui->comboBoxAddr->addItem(tmp.toString());
        }
    }
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
                                         "客户端端口号："+QString::number(connction->peerPort()) +"\n");//::xxx:192.168.1.9

        connect(connction,SIGNAL(readyRead()),this,SLOT(on_readyRead_handler()));
    }
}

void Widget::on_readyRead_handler()
{
    QTcpSocket *tmpSock = qobject_cast<QTcpSocket *>(sender());

    QByteArray revData = tmpSock->readAll();
    ui->textEditRev->insertPlainText("客户端: " + revData);
}


void Widget::on_btnListen_clicked()
{
    //bool QTcpServer::listen(const QHostAddress &address = QHostAddress::Any, quint16 port = 0) 8888--15000
    //QHostAddress addr("192.168.1.9");
    int port = ui->lineEditPort->text().toInt();
    //if(!server->listen(QHostAddress::Any,port)){
    if(!server->listen(QHostAddress(ui->comboBoxAddr->currentText()),port)){
        qDebug() << "listenError";
        QMessageBox msgBox;
        msgBox.setWindowTitle("监听失败");
        msgBox.setText("端口号被占用");
        msgBox.exec();
        return;
    }
    ui->btnListen->setEnabled(false);
    ui->btnLineout->setEnabled(true);
    ui->btnStopListen->setEnabled(true);
}
