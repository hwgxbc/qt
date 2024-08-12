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

    //控制参数初始化
    writeCntTotal = 0;
    readCntTotal  = 0;
    serialStatus = false;
    ui->btnSendContext->setEnabled(false);
    ui->checkBSendInTime->setEnabled(false);

    //在窗口加入一个串口控制对象
    serialPort = new QSerialPort(this);

    //定义一个定时器，每个100ms刷新以下系统时间显示
    QTimer *getSysTimeTimer = new QTimer(this);
    connect(getSysTimeTimer,SIGNAL(timeout()),this,SLOT(time_reflash()));
    getSysTimeTimer->start(100);

    //这个定时器用于定时发送
    timer = new QTimer(this);

    connect(serialPort,&QSerialPort::readyRead,this,&Widget::on_SerialData_readyToRead);
    connect(timer,&QTimer::timeout,[=](){
        on_btnSendContext_clicked();
    });

    ui->comboBox_boautrate->setCurrentIndex(6);
    ui->comboBox_databit->setCurrentIndex(3);

    //检测系统可用串口，并更新到comboBox上待用户选择
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

}

//发送按键被按下
void Widget::on_btnSendContext_clicked()
{
    int writeCnt = 0;
    //读取内容
    const char* sendData = ui->lineEditSendContext->text().toLocal8Bit().constData();
    //通过串口发送
    if(ui->checkBHexSend->isChecked()){

        QString tmp = ui->lineEditSendContext->text();
        //判断是否是偶数位
        QByteArray tmpArray = tmp.toLocal8Bit();
        if(tmpArray.size() % 2 != 0){
            ui->labelSendStatus->setText("Error Input!");
            return;
        }
        //判读是否是符合16进制的表达
        for(char c : tmpArray){
            if( !std::isxdigit(c)){
                ui->labelSendStatus->setText("Error Input!");
                return;
            }
        }
        //转换成16进制发送，用户输入1，变成1,拒绝变成字符1，ASSII 49
        QByteArray arraySend = QByteArray::fromHex(tmpArray);

        writeCnt = serialPort->write(arraySend);

    }else{
        writeCnt = serialPort->write(sendData);
    }
    if(writeCnt == -1){
        ui->labelSendStatus->setText("SendError!");
    }else{
        //统计累加发送的数据量
        writeCntTotal+=writeCnt;
        qDebug() << "SendOK" << sendData;
        //更新发送状态，更新发送总数据总量
        ui->labelSendStatus->setText("SendOK!");
        ui->labelSendcnt->setText("Sent:"+QString::number(writeCntTotal));
        //更新发送记录，做重复处理
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

        if(ui->checkBHexDisplay->isChecked()){
            QByteArray tmpHexString = revMessage.toUtf8().toHex();
            //原来控件上的内容,hex
            QString tmpStringHex = ui->textEditRev->toPlainText(); //因为勾选了，读出来的就是hex
            tmpHexString = tmpStringHex.toUtf8() + tmpHexString; //把读出的旧的hex和新收到的数据转成hex进行拼接
            //重新显示在控件上
            ui->textEditRev->setText(QString::fromUtf8(tmpHexString));
        }else{
            if(ui->checkBrevTime->checkState()== Qt::Unchecked){
                ui->textEditRev->append(revMessage);
            }
            else if(ui->checkBrevTime->checkState()== Qt::Checked){
                getSysTime();
                ui->textEditRev->append("【"+myTime+"】 "+revMessage);
            }
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
        //关闭串口后，设置各个控件的使能，恢复可配置状态
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
        // 关闭定时器
        timer->stop();
        ui->lineEditTimeeach->setEnabled(true);
        ui->lineEditSendContext->setEnabled(true);

    }
}


void Widget::on_checkBSendInTime_clicked(bool checked)
{
    // 如果定时发送被勾选
    if(checked){
        //处理控件，设置时间和发送内容不可编辑
        ui->lineEditTimeeach->setEnabled(false);
        ui->lineEditSendContext->setEnabled(false);
        //启动定时器，定时时间根据控件用户设定的
        timer->start(ui->lineEditTimeeach->text().toInt());
        //on_btnSendContext_clicked();
    }else{
        //如果定时发送取消，则停止定时器
        timer->stop();
        //设置发送时间和发送内容可编辑状态
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
   //弹出对话框，选择文件保存位置
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "D:/QT/serialData.txt",
                                                    tr("Text (*.txt)"));
    if(fileName != NULL){
        //新建文件
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        //把控件上的数据读出后写入文件
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
    //处理日期
    QDate date = currentTime.date();
    int year = date.year();
    int month = date.month();
    int day = date.day();
    //处理时间
    QTime time = currentTime.time();
    int hour = time.hour();
    int minite = time.minute();
    int second = time.second();
    //格式化成 2024-01-01  23:12:05
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
        //1. 读取textEdit上的内容
        QString tmp = ui->textEditRev->toPlainText();
        //2. 转换成hex
        QByteArray qtmp = tmp.toUtf8();
        qtmp = qtmp.toHex();
        //3. 显示
        QString lastShow;
        tmp  = QString::fromUtf8(qtmp); // 56 78
        for(int i=0; i<tmp.size();i+=2){
            //56
            lastShow += tmp.mid(i,2) + " ";
        }
        ui->textEditRev->setText(lastShow.toUpper());
    }else{
        //1. 读取textEdit上的内容，hex
        QString tmpHexString = ui->textEditRev->toPlainText();
        QByteArray tmpHexQBytearray = tmpHexString.toUtf8();
        QByteArray tmpQByteString = QByteArray::fromHex(tmpHexQBytearray);
        ui->textEditRev->setText(QString::fromUtf8(tmpQByteString));
    }
}
