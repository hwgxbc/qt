#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QMenu>
#include <QNetworkReply>
#include <QWidget>
#include "citycodeutils.h"
#include "day.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Day days[7];
    QList<QLabel *> mDateList;
    QList<QLabel *> mWeekList;
    QList<QLabel *> mIconList;
    QList<QLabel *> mWeaTypeList;
    QList<QLabel *> mAirqList;
    QList<QLabel *> mFxList;
    QList<QLabel *> mFlList;



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
    QMap<QString,QString> mTypeMap;
    void parseWeatherJsonData(QByteArray rawData);
    void parseWeatherJsonDataNew(QByteArray rawData);
    void updateUI();

};
#endif // WIDGET_H
