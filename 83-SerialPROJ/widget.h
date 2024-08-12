#ifndef WIDGET_H
#define WIDGET_H

#include <QSerialPort>
#include <QTimer>
#include <QWidget>

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
    void on_btnCloseOrOpenSerial_clicked();

    void on_btnSendContext_clicked();

    void on_SerialData_readyToRead();
    void on_btnCloseOrOpenSerial_clicked(bool checked);

    void on_checkBSendInTime_clicked(bool checked);

private:
    Ui::Widget *ui;
    QSerialPort *serialPort;
    int writeCntTotal;
    int readCntTotal;
    QString sendBak;
    bool serialStatus;
    QTimer *timer;
};
#endif // WIDGET_H
