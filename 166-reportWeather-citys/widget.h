#ifndef WIDGET_H
#define WIDGET_H

#include <QMenu>
#include <QNetworkReply>
#include <QWidget>
#include "citycodeutils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:

    void readHttpRply(QNetworkReply *reply);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QMenu *menuQuit;
    QPoint mOffset;
    QNetworkReply *reply;
    QString strUrl;
    QNetworkAccessManager *manager;
    CityCodeUtils cityCodeUtils;
    void parseWeatherJsonData(QByteArray rawData);
};
#endif // WIDGET_H
