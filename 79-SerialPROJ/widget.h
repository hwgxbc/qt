#ifndef WIDGET_H
#define WIDGET_H

#include <QSerialPort>
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
private:
    Ui::Widget *ui;
    QSerialPort *serialPort;
    int writeCntTotal;
    int readCntTotal;
    QString sendBak;
};
#endif // WIDGET_H
