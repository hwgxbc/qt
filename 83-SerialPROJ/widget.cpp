#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayoutGlobal);

    writeCntTotal = 0;
    readCntTotal  = 0;
    serialStatus = false;
    ui->btnSendContext->setEnabled(false);
    ui->checkBSendInTime->setEnabled(false);

    serialPort = new QSerialPort(this);
    timer = new QTimer(this);

    connect(serialPort,&QSerialPort::readyRead,this,&Widget::on_SerialData_readyToRead);
    connect(timer,&QTimer::timeout,[=](){
        on_btnSendContext_clicked();
    });

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
   /* qDebug() << "none checked";
    if(!serialStatus){
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
            ui->comboBox_databit->setEnabled(false);
            ui->comboBox_fileCon->setEnabled(false);
            ui->comboBox_jiaoyan->setEnabled(false);
            ui->comboBox_stopbit->setEnabled(false);
            ui->comboBox_boautrate->setEnabled(false);
            ui->comboBox_serialNum->setEnabled(false);
            ui->btnCloseOrOpenSerial->setText("关闭串口");
            ui->btnSendContext->setEnabled(true);
            serialStatus = true;
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("打开串口错误");
            msgBox.setText("打开失败，串口可能被占用或者已拔出！");
            msgBox.exec();
        }
    }else{
        serialPort->close();
        ui->btnCloseOrOpenSerial->setText("打开串口");
        ui->comboBox_databit->setEnabled(true);
        ui->comboBox_fileCon->setEnabled(true);
        ui->comboBox_jiaoyan->setEnabled(true);
        ui->comboBox_stopbit->setEnabled(true);
        ui->comboBox_boautrate->setEnabled(true);
        ui->comboBox_serialNum->setEnabled(true);
        serialStatus = false;
        ui->btnSendContext->setEnabled(false);
    }*/
}

void Widget::on_btnSendContext_clicked()
{
    int writeCnt = 0;
    const char* sendData = ui->lineEditSendContext->text().toLocal8Bit().constData();

    writeCnt = serialPort->write(sendData);

    if(writeCnt == -1){
        ui->labelSendStatus->setText("SendError!");
    }else{
        writeCntTotal+=writeCnt;
        qDebug() << "SendOK" << sendData;

        ui->labelSendStatus->setText("SendOK!");
        //ui->labelSendcnt->setNum(writeCntTotal);
        ui->labelSendcnt->setText("Sent:"+QString::number(writeCntTotal));

        if(strcmp(sendData,sendBak.toStdString().c_str()) != 0){
            ui->textEditRecord->append(sendData);
            sendBak = QString::fromUtf8(sendData);
        }
    }
}

void Widget::on_SerialData_readyToRead()
{

    QString revMessage = serialPort->readAll();
    if(revMessage != NULL){
        qDebug() << "getMessage:"<< revMessage;
        ui->textEditRev->append(revMessage);
        readCntTotal += revMessage.size();
        //ui->labelRevcnt->setNum(readCntTotal);
        ui->labelRevcnt->setText("Received:"+QString::number(readCntTotal));
    }
}

void Widget::on_btnCloseOrOpenSerial_clicked(bool checked)
{
    //qDebug() << "IN checked" << checked;
    if(checked){
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
            ui->comboBox_databit->setEnabled(false);
            ui->comboBox_fileCon->setEnabled(false);
            ui->comboBox_jiaoyan->setEnabled(false);
            ui->comboBox_stopbit->setEnabled(false);
            ui->comboBox_boautrate->setEnabled(false);
            ui->comboBox_serialNum->setEnabled(false);
            ui->btnCloseOrOpenSerial->setText("关闭串口");
            ui->btnSendContext->setEnabled(true);
            ui->checkBSendInTime->setEnabled(true);
           // serialStatus = true;
        }else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("打开串口错误");
            msgBox.setText("打开失败，串口可能被占用或者已拔出！");
            msgBox.exec();
        }
    }else{
        serialPort->close();
        ui->btnCloseOrOpenSerial->setText("打开串口");
        ui->comboBox_databit->setEnabled(true);
        ui->comboBox_fileCon->setEnabled(true);
        ui->comboBox_jiaoyan->setEnabled(true);
        ui->comboBox_stopbit->setEnabled(true);
        ui->comboBox_boautrate->setEnabled(true);
        ui->comboBox_serialNum->setEnabled(true);
       // serialStatus = false;
        ui->btnSendContext->setEnabled(false);
        ui->checkBSendInTime->setEnabled(false);
        ui->checkBSendInTime->setCheckState(Qt::Unchecked);
        timer->stop();
        ui->lineEditTimeeach->setEnabled(true);
        ui->lineEditSendContext->setEnabled(true);

    }
}


void Widget::on_checkBSendInTime_clicked(bool checked)
{
   // qDebug() <<"checkBsendIntime:"<<checked;
    if(checked){
        ui->lineEditTimeeach->setEnabled(false);
        ui->lineEditSendContext->setEnabled(false);
        timer->start(ui->lineEditTimeeach->text().toInt());
           //on_btnSendContext_clicked();
    }else{
        timer->stop();
        ui->lineEditTimeeach->setEnabled(true);
        ui->lineEditSendContext->setEnabled(true);
    }
}
