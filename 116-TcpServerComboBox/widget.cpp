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

    connect(ui->comboBoxChildren,&MyComboBox::on_ComboBox_clicked,this,&Widget::mComboBox_refresh);
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
        //void QAbstractSocket::disconnected()
        // connect(connction,SIGNAL(disconnected()),this,SLOT(mdisconnected()));
        //void QAbstractSocket::stateChanged(QAbstractSocket::SocketState socketState)
        connect(connction,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                this,SLOT(mstateChanged(QAbstractSocket::SocketState)));
    }
}

void Widget::on_readyRead_handler()
{
    QTcpSocket *tmpSock = qobject_cast<QTcpSocket *>(sender());

    QByteArray revData = tmpSock->readAll();
    ui->textEditRev->insertPlainText("客户端: " + revData);
}

void Widget::mdisconnected()
{
    QTcpSocket *tmpSock = qobject_cast<QTcpSocket *>(sender());
    qDebug() << "client out!";
    ui->textEditRev->insertPlainText("客户端断开！");
    tmpSock->deleteLater();
}

void Widget::mstateChanged(QAbstractSocket::SocketState socketState)
{
    QTcpSocket *tmpSock = qobject_cast<QTcpSocket *>(sender());
    qDebug() << "client out In state:" << socketState;
    switch(socketState){
    case QAbstractSocket::UnconnectedState:
        //case QAbstractSocket::ClosingState:
        ui->textEditRev->insertPlainText("客户端断开！");
        tmpSock->deleteLater();
        break;
    case QAbstractSocket::ConnectedState:
    case QAbstractSocket::ConnectingState:
        ui->textEditRev->insertPlainText("客户端接入！");
        break;
    }
}

void Widget::mComboBox_refresh()
{
    ui->comboBoxChildren->clear();
    QList<QTcpSocket*> tcpSocketClients =  server->findChildren<QTcpSocket*>();

    for(QTcpSocket* tmp:tcpSocketClients){
        if(tmp!=nullptr)
           ui->comboBoxChildren->addItem(QString::number(tmp->peerPort()));
    }
    ui->comboBoxChildren->addItem("all");
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

void Widget::on_btnSend_clicked()
{
    QList<QTcpSocket*> tcpSocketClients =  server->findChildren<QTcpSocket*>();
    //当用户不选择向all，所有客户端进行发送的时候
    qDebug() << childIndex;
    if(ui->comboBoxChildren->currentText() != "all"){
        //根据用户选择，找到指定客户端进行数据通信，通过childInde来查找，该变量在用户选择条目后触发的on_comboBoxChildren_activated去赋值

        tcpSocketClients[childIndex]->write(ui->textEditSend->toPlainText().toStdString().c_str());
    }else{
        //遍历所有子客户端，并一一调用write函数，向所有客户端发送
        for(QTcpSocket* tmp:tcpSocketClients){
            tmp->write(ui->textEditSend->toPlainText().toStdString().c_str());
        }
    }
}

void Widget::on_comboBoxChildren_activated(int index)
{
    childIndex = index;
}
