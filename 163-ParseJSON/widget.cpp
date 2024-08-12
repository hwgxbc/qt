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
    //第一步：读取JSON文件保存到QByteArray中
    QFile file("D:/QT/test.json");
    file.open(QIODevice::ReadOnly);
    QByteArray rawData = file.readAll();
    file.close();
    //第二步：把QByteArray转成JSONDoc
    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData);
    if( !jsonDoc.isNull() && jsonDoc.isObject()){
        //第三步：把JsonDoc转成JsonObj
        QJsonObject jsonRoot = jsonDoc.object();
        //第四步：如果解析普通键值对，通过“下表键”来获取值
        QString strW      = jsonRoot["weather"].toString();
        QString strCityId = jsonRoot["cityid"].toString();
        int tempretrue = jsonRoot["tmp"].toInt();

        qDebug() << strW;
        qDebug() << strCityId;
        qDebug() << QString::number(tempretrue);
        //第五步：判读是否是一个数组
        if(jsonRoot.contains("testArry") && jsonRoot["testArry"].isArray()){
            qDebug() << "array";
            //如果是数组，转换成JSON数组
            QJsonArray testArray = jsonRoot["testArry"].toArray();
            //遍历数组，访问每一项
            for(QJsonValue val : testArray){
                //QJsonValue的type函数返回数据类型，根据不同的数据类型处理数据
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
        //第六步：判断某个键对应的值，是否是一个json对象
        if(jsonRoot.contains("alam") && jsonRoot["alam"].isObject()){
            //转成Json对象后处理
            QJsonObject alamObj = jsonRoot["alam"].toObject();
            qDebug() << alamObj["alamLeve"].toString();
            qDebug() << alamObj["alamTitle"].toString();
            qDebug() << alamObj["alamType"].toString();
        }

        if(jsonRoot.contains("days") && jsonRoot["days"].isArray()){
            QJsonArray dayArray = jsonRoot["days"].toArray();
            for(QJsonValue val : dayArray){
                //if(val.type() ==QJsonValue::Object ){
                if(val.isObject()){
                    QJsonObject obj = val.toObject();
                    qDebug() << obj["day"].toString();
                    qDebug() << QString::number(obj["tem"].toDouble());
                    qDebug() << obj["wea"].toString();
                }
            }
        }

    }
}

Widget::~Widget()
{
    delete ui;
}

