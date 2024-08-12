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

    QJsonArray jsonArray;
    jsonArray.append("data1");
    jsonArray.append("data2");
    jsonArray.append("data3");
    jsonArray.append(100);

    rootObj["testArry"] = jsonArray;

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

