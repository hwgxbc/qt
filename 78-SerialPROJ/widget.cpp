#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayoutGlobal);
    serialPort = new QSerialPort(this);

    connect(serialPort,&QSerialPort::readyRead,this,&Widget::on_SerialData_readyToRead);

    ui->comboBox_boautrate->setCurrentIndex(6);
    ui->comboBox_databit->setCurrentIndex(3);

    QList<QSerialPortInfo> serialList = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo serialInfo : serialList){
        qDebug() << serialInfo.portName();
        ui->comboBox_serialNum->addItem(serialInfo.portName());

    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnCloseOrOpenSerial_clicked()
{
    //1. 选择端口号
    serialPort->setPortName(ui->comboBox_serialNum->currentText());
    //2. 配置波特率
    serialPort->setBaudRate(ui->comboBox_boautrate->currentText().toInt());
    //3. 配置数据位
    serialPort->setDataBits(QSerialPort::DataBits(
                                ui->comboBox_databit->currentText().toUInt()));
    //4. 配置校验位
    switch (ui->comboBox_jiaoyan->currentIndex()) {
    case 0:
        serialPort->setParity(QSerialPort::NoParity);
        break;
    case 1:
        break;
        serialPort->setParity(QSerialPort::EvenParity);
    case 2:
        serialPort->setParity(QSerialPort::MarkParity);
        break;
    case 3:
        serialPort->setParity(QSerialPort::OddParity);
        break;
    case 4:
        serialPort->setParity(QSerialPort::SpaceParity);
        break;
    default:
        serialPort->setParity(QSerialPort::UnknownParity);
        break;

    }
    //5. 配置停止位
    serialPort->setStopBits(QSerialPort::StopBits(
                                ui->comboBox_databit->currentText().toUInt()));
    //6. 流控
    if(ui->comboBox_fileCon->currentText() == "None")
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
    //7. 打开串口
    if(serialPort->open(QIODevice::ReadWrite)){
        qDebug() << "serial open success";
    }
}

void Widget::on_btnSendContext_clicked()
{
    const char* sendData = ui->lineEditSendContext->text().toStdString().c_str();
    serialPort->write(sendData);
    qDebug() << "SendOK" << sendData;
    ui->textEditRecord->append(sendData);
}

void Widget::on_SerialData_readyToRead()
{
    QString revMessage = serialPort->readAll();
    qDebug() << "getMessage:"<< revMessage;
    ui->textEditRev->append(revMessage);
}
