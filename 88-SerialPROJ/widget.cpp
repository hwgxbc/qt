#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>

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

    QTimer *getSysTimeTimer = new QTimer(this);
    connect(getSysTimeTimer,SIGNAL(timeout()),this,SLOT(time_reflash()));
    getSysTimeTimer->start(100);

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
        if(ui->checkBrevTime->checkState()== Qt::Unchecked){
            ui->textEditRev->append(revMessage);
        }
        else if(ui->checkBrevTime->checkState()== Qt::Checked){
            getSysTime();
            ui->textEditRev->append("【"+myTime+"】 "+revMessage);
        }

        readCntTotal += revMessage.size();

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

void Widget::on_btnrevClear_clicked()
{
    ui->textEditRev->setText("");
}

void Widget::on_btnrevSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "D:/QT/serialData.txt",
                                                    tr("Text (*.txt)"));
    if(fileName != NULL){
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << ui->textEditRev->toPlainText();
        file.close();
    }
}

void Widget::time_reflash()
{
    getSysTime();
    ui->labelCurrentTime->setText(myTime);
}

void Widget::getSysTime()
{
    QDateTime currentTime = QDateTime::currentDateTime();

    QDate date = currentTime.date();
    int year = date.year();
    int month = date.month();
    int day = date.day();

    QTime time = currentTime.time();
    int hour = time.hour();
    int minite = time.minute();
    int second = time.second();

    myTime = QString("%1-%2-%3  %4:%5:%6")
            .arg(year, 2, 10, QChar('0'))
            .arg(month, 2, 10, QChar('0'))
            .arg(day, 2, 10, QChar('0'))
            .arg(hour, 2, 10, QChar('0'))
            .arg(minite, 2, 10, QChar('0'))
            .arg(second, 2, 10, QChar('0'));
}

void Widget::on_checkBHexDisplay_clicked(bool checked)
{
    if(checked){
        //1. 读取TextEdit上的数据，是QString类型
        QString tmp = ui->textEditRev->toPlainText();
        //2. 转换成QByteArray,这个类有个函数toHex
        QByteArray tmpByteArray = tmp.toUtf8();
        tmpByteArray = tmpByteArray.toHex();
        //3. 把hex形态的QByteArray转成QString，再显示
        ui->textEditRev->setText(QString::fromUtf8(tmpByteArray));
    }else{
        //1. 读取TextEdit上的数据，是QString类型,此时是Hex形态的
        QString tmp = ui->textEditRev->toPlainText();
        //2. 转换成QByteArray,这个类有个函数fromHex,把Hex形态的QByteArray转成QString形态的QByteArray
        QByteArray tmpByteArray = tmp.toUtf8();
        tmpByteArray = QByteArray::fromHex(tmpByteArray);
        //3.把QByteArray转成QString，再显示
        ui->textEditRev->setText(QString::fromUtf8(tmpByteArray));
    }
}
