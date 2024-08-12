#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);

    ui->btndiscon->setEnabled(false);
    ui->btnSend->setEnabled(false);

    client = new QTcpSocket(this);
    connect(client,SIGNAL(readyRead()),this,SLOT(mRead_Data_From_Server()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnConnect_clicked()
{

//    virtual void
//    connectToHost(const QHostAddress &address, quint16 port, QIODevice::OpenMode openMode = ReadWrite)
    client->connectToHost(ui->lineEditIPAddr->text(),ui->lineEditPort->text().toInt());
    if(client->state() == QAbstractSocket::ConnectedState ||
            client->state()==QAbstractSocket::ConnectingState){
        ui->textEditRev->append("连接成功！");
        ui->btnConnect->setEnabled(false);
        ui->lineEditPort->setEnabled(false);
        ui->lineEditIPAddr->setEnabled(false);
        ui->btndiscon->setEnabled(true);
        ui->btnSend->setEnabled(true);
    }

}

void Widget::mRead_Data_From_Server()
{
    ui->textEditRev->insertPlainText(client->readAll());
}

void Widget::on_btnSend_clicked()
{
    client->write(ui->textEditSend->toPlainText().toUtf8());
}

void Widget::on_btndiscon_clicked()
{
    client->close();
    ui->textEditRev->append("断开连接！");
    ui->btnConnect->setEnabled(true);
    ui->lineEditPort->setEnabled(true);
    ui->lineEditIPAddr->setEnabled(true);
    ui->btndiscon->setEnabled(false);
    ui->btnSend->setEnabled(false);

}
