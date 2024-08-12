#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>
#include <QNetworkInterface>
#include <QTcpSocket>
#include <QTextCodec>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    server = new QTcpServer(this);

    connect(ui->comboBoxChildren,&MyComboBox::on_ComboBox_clicked,this,&Widget::mComboBox_refresh);
    connect(server,SIGNAL(newConnection()),this,SLOT(on_newClient_connect()));
    ui->btnLineout->setEnabled(false);
    ui->btnStopListen->setEnabled(false);
    ui->btnSend->setEnabled(false);

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
        connect(connction,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                this,SLOT(mstateChanged(QAbstractSocket::SocketState)));

        ui->comboBoxChildren->addItem(QString::number(connction->peerPort()));
        ui->comboBoxChildren->setCurrentText(QString::number(connction->peerPort()));

        if(!ui->btnSend->isEnabled()){
            ui->btnSend->setEnabled(true);
        }
    }
}

void Widget::on_readyRead_handler()
{
    QTcpSocket *tmpSock = qobject_cast<QTcpSocket *>(sender());

    QByteArray revData = tmpSock->readAll();
    ui->textEditRev->moveCursor(QTextCursor::End);
    ui->textEditRev->ensureCursorVisible();
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
    int tmpIndex;
    QTcpSocket *tmpSock = qobject_cast<QTcpSocket *>(sender());
    qDebug() << "client out In state:" << socketState;
    switch(socketState){
    case QAbstractSocket::UnconnectedState:
        //case QAbstractSocket::ClosingState:
        ui->textEditRev->insertPlainText("客户端断开！");
        tmpIndex = ui->comboBoxChildren->findText(QString::number(tmpSock->peerPort()));
        ui->comboBoxChildren->removeItem(tmpIndex);
        tmpSock->deleteLater();
        if(ui->comboBoxChildren->count() == 0)
            ui->btnSend->setEnabled(false);
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
    if(tcpSocketClients.isEmpty()){
        QMessageBox msgBox;
        msgBox.setWindowTitle("发送错误！");
        msgBox.setText("当前无连接!");
        msgBox.exec();
        ui->btnSend->setEnabled(false);
        return;
    }
    //当用户不选择向all，所有客户端进行发送的时候

    if(ui->comboBoxChildren->currentText() != "all"){

        QString currentName = ui->comboBoxChildren->currentText();
        for(QTcpSocket* tmp : tcpSocketClients){
            if(QString::number(tmp->peerPort()) == currentName){
                tmp->write(ui->textEditSend->toPlainText().toStdString().c_str());
            }
        }
       // tcpSocketClients[childIndex]->write(ui->textEditSend->toPlainText().toStdString().c_str());
    }else{
        //遍历所有子客户端，并一一调用write函数，向所有客户端发送
        for(QTcpSocket* tmp:tcpSocketClients){
            QByteArray sendData = ui->textEditSend->toPlainText().toLocal8Bit();
            tmp->write(sendData);
        }
    }
}


void Widget::on_btnStopListen_clicked()
{
    QList<QTcpSocket*> tcpSocketClients =  server->findChildren<QTcpSocket*>();
    for(QTcpSocket* tmp:tcpSocketClients){
        tmp->close();
    }

    server->close();
    ui->btnListen->setEnabled(true);
    ui->btnLineout->setEnabled(false);
    ui->btnStopListen->setEnabled(false);

}

void Widget::on_btnLineout_clicked()
{
    on_btnStopListen_clicked();
    delete server;
    this->close();
}
