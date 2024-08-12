#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QJsonObject rootObj;
    rootObj["cityid"]  = "1010100";
    rootObj["date"]    = "2024-01-23";
    rootObj["weather"] = "雨夹雪";
    rootObj["tmp"]     = 3;
    //Json数组
    QJsonArray jsonArray;
    jsonArray.append("data1");
    jsonArray.append("data2");
    jsonArray.append("data3");
    jsonArray.append(100);

    rootObj["testArry"] = jsonArray;

    QJsonObject alarmObj;
    alarmObj["alamType"] = "雪灾";
    alarmObj["alamLeve"] = "黄色";
    alarmObj["alamTitle"] = "福州市警告老陈多穿点衣服";
    rootObj["alam"] = alarmObj;

    QJsonObject day0;
    day0["day"] = "星期一";
    day0["wea"] = "晴";
    day0["tem"] = 5.7;

    QJsonObject day1;
    day1["day"] = "星期二";
    day1["wea"] = "晴";
    day1["tem"] = 7;

    QJsonObject day2;
    day2["day"] = "星期三";
    day2["wea"] = "多云";
    day2["tem"] = 17;

    QJsonArray dayArray;
    dayArray.append(day0);
    dayArray.append(day1);
    dayArray.append(day2);

    rootObj["days"] = dayArray;


    //通过QJsonDocument把JSON数据转换成QByteArray
    QJsonDocument jsonDoc(rootObj);
    QByteArray jsonArry = jsonDoc.toJson();

    QFile file("D:/QT/test.json");
    file.open(QIODevice::WriteOnly);
    file.write(jsonArry);
    file.close();
}

Widget::~Widget()
{
    delete ui;
}

