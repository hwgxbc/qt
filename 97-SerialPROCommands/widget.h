#ifndef WIDGET_H
#define WIDGET_H

#include <QSerialPort>
#include <QTimer>
#include <QWidget>
#include "mycombobox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    //此函数作废
    void on_btnCloseOrOpenSerial_clicked();
    //发送槽函数
    void on_btnSendContext_clicked();
    //接收槽函数
    void on_SerialData_readyToRead();
    //打开.关闭串口，按键带checked
    void on_btnCloseOrOpenSerial_clicked(bool checked);
    //发送是否带时间
    void on_checkBSendInTime_clicked(bool checked);
    //清空接收区
    void on_btnrevClear_clicked();
    //保存接收记录到文件
    void on_btnrevSave_clicked();
    //刷新时间显示
    void time_reflash();
    //是否16进制显示
    void on_checkBHexDisplay_clicked(bool checked);

    void on_btnhideTable_clicked(bool checked);

    void on_btnHideHistory_clicked(bool checked);

    void refreshSerialName();

    void on_command_button_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *serialPort;

    //用于统计接收和读取的总字节数
    int writeCntTotal;
    int readCntTotal;
    //用于比较发送记录
    QString sendBak;
    //用于实时获取系统时间
    QString myTime;
    //用于显示程序串口动作的状态
    bool serialStatus;
    //定时器用于刷新界面上的系统时间
    QTimer *timer;
    //用于更新私有变量myTime
    void getSysTime();

};
#endif // WIDGET_H
