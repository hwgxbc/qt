#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //读取JSON文件保存到QByteArray中
    QFile file("D:/QT/test.json");
    file.open(QIODevice::ReadOnly);
    QByteArray rawData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData);
    if( !jsonDoc.isNull() && jsonDoc.isObject()){
        QJsonObject jsonRoot = jsonDoc.object();
        QString strW      = jsonRoot["weather"].toString();
        QString strCityId = jsonRoot["cityid"].toString();
        int tempretrue = jsonRoot["tmp"].toInt();

        qDebug() << strW;
        qDebug() << strCityId;
        qDebug() << QString::number(tempretrue);

        if(jsonRoot.contains("testArry") && jsonRoot["testArry"].isArray()){
            qDebug() << "array";
            QJsonArray testArray = jsonRoot["testArry"].toArray();
            for(QJsonValue val : testArray){
               // QJsonValue::Type t = val.type();
                switch (val.type()) {
                    case QJsonValue::Double:
                    qDebug() << QString::number(val.toDouble());
                    break;
                case QJsonValue::String:
                    qDebug() << val.toString();
                    break;
                case QJsonValue::Object:
                    break;
                }

            }
        }
        if(jsonRoot.contains("alam") && jsonRoot["alam"].isObject()){
            QJsonObject alamObj = jsonRoot["alam"].toObject();
            qDebug() << alamObj["alamLeve"].toString();
            qDebug() << alamObj["alamTitle"].toString();
            qDebug() << alamObj["alamType"].toString();
        }

    }
}

Widget::~Widget()
{
    delete ui;
}

