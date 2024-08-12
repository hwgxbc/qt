#ifndef WIDGET_H
#define WIDGET_H

#include <QTcpSocket>
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
    void on_btnConnect_clicked();
    void mRead_Data_From_Server();

    void on_btnSend_clicked();

    void on_btndiscon_clicked();

    void onConnected();

    void onError(QAbstractSocket::SocketError);

    void onTimeOUt();

private:
    Ui::Widget *ui;
    QTcpSocket *client;
    QTimer *timer;
    void mInserTextByColor(Qt::GlobalColor color,QString str);
};
#endif // WIDGET_H
