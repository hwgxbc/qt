#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QTcpServer* server;
public slots:
    void on_newClient_connect();

private slots:
    void on_btnListen_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
