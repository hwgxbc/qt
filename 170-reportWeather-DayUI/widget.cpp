#include "widget.h"
#include "ui_widget.h"

#include <QMouseEvent>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFont(QFont("Arial",15));
    setFixedSize(507,936);
    setWindowFlag(Qt::FramelessWindowHint);
    //新建一个菜单组件
    menuQuit = new QMenu(this);
    //设置菜单项文字颜色
    menuQuit->setStyleSheet("QMenu::item {color:white}");
    //为菜单组件添加一个动作
    QAction *closeAct = new QAction(QIcon(":/res/close.png"), tr("退出"), this);
    menuQuit->addAction(closeAct);
    //用户选择菜单项并点击后回调函数，退出程序
    connect(menuQuit,&QMenu::triggered,this,[=]{
        this->close();
    });
    //由QNetworkAccessManager发起get请求
    manager = new QNetworkAccessManager(this);
    //strUrl = "http://v1.yiketianqi.com/api?unescape=1&version=v61&appid=26371314&appsecret=qOhoD413";
    strUrl = "http://v1.yiketianqi.com/api?unescape=1&version=v9&appid=26371314&appsecret=qOhoD413";
    QUrl urlTianQi(strUrl);
    //指定请求的url地址
    QNetworkRequest res(urlTianQi);
    reply =  manager->get(res);
    //QNetworkRequest网络请求后进行数据读取
    connect(manager,&QNetworkAccessManager::finished,this,&Widget::readHttpRply);

    mWeekList << ui->labelday0 << ui->labelday1
              << ui->labelday2 << ui->labelday3
              << ui->labelday4 << ui->labelday5;
    mDateList << ui->labelDate0 << ui->labelDate1
              << ui->labelDate2 << ui->labelDate3
              << ui->labelDate4 << ui->labelDate5;
    mIconList << ui->labelWheatherIcon0 << ui->labelWheatherIcon1
              << ui->labelWheatherIcon2 << ui->labelWheatherIcon3
              << ui->labelWheatherIcon4 << ui->labelWheatherIcon5;
    mWeaTypeList << ui->lbweatherTypeDate0 << ui->lbweatherTypeDate1
                 << ui->lbweatherTypeDate2 << ui->lbweatherTypeDate3
                 << ui->lbweatherTypeDate4 << ui->lbweatherTypeDate5;
    mAirqList << ui->labelaiq0 << ui->labelaiq1
              << ui->labelaiq2 << ui->labelaiq3
              << ui->labelaiq4 << ui->labelaiq5;
    mFxList << ui->labelFX0 << ui->labelFX1
            << ui->labelFX2 << ui->labelFX3
            << ui->labelFX4 << ui->labelFX5;
    mFlList << ui->labelFL0 << ui->labelFL1
            << ui->labelFL2 << ui->labelFL3
            << ui->labelFL4 << ui->labelFL5;

    //根据keys,设置icon的路径
    mTypeMap.insert("暴雪",":/res/type/BaoXue.png");
    mTypeMap.insert("暴雨",":/res/type/BaoYu. png");
    mTypeMap.insert("暴雨到大暴雨",":/res/type/BaoYuDaoDaBaoYu.png");
    mTypeMap.insert("大暴雨",":/res/type/DaBaoYu.png");
    mTypeMap.insert("大暴雨到特大暴雨",":/res/type/DaBaoYuDaoTeDaBaoYu.png");
    mTypeMap.insert("大到暴雪",":/res/type/DaDaoBaoXue.png");
    mTypeMap.insert("大雪",":/res/type/DaXue.png");
    mTypeMap.insert("大雨",":/res/type/DaYu.png");
    mTypeMap.insert("冻雨",":/res/type/DongYu.png");
    mTypeMap.insert("多云",":/res/type/DuoYun.png");
    mTypeMap.insert("浮沉",":/res/type/FuChen.png");
    mTypeMap.insert("雷阵雨",":/res/type/LeiZhenYu.png");
    mTypeMap.insert("雷阵雨伴有冰雹",":/res/type/LeiZhenYuBanYouBingBao.png");
    mTypeMap.insert("霾",":/res/type/Mai.png");
    mTypeMap.insert("强沙尘暴",":/res/type/QiangShaChenBao.png");
    mTypeMap.insert("晴",":/res/type/Qing.png");
    mTypeMap.insert("沙尘暴",":/res/type/ShaChenBao.png");
    mTypeMap.insert("特大暴雨",":/res/type/TeDaBaoYu.png");
    mTypeMap.insert("undefined",":/res/type/undefined.png");
    mTypeMap.insert("雾",":/res/type/Wu.png");
    mTypeMap.insert("小到中雪",":/res/type/XiaoDaoZhongXue.png");
    mTypeMap.insert("小到中雨",":/res/type/XiaoDaoZhongYu.png");
    mTypeMap.insert("小雪",":/res/type/XiaoXue.png");
    mTypeMap.insert("小雨",":/res/type/XiaoYu.png");
    mTypeMap.insert("雪",":/res/type/Xue.png");
    mTypeMap.insert("扬沙",":/res/type/YangSha.png");
    mTypeMap.insert("阴",":/res/type/Yin.png");
    mTypeMap.insert("雨",":/res/type/Yu.png");
    mTypeMap.insert("雨夹雪",":/res/type/YuJiaXue.png");
    mTypeMap.insert("阵雪",":/res/type/ZhenXue.png");
    mTypeMap.insert("阵雨",":/res/type/ZhenYu.png");
    mTypeMap.insert("中到大雪",":/res/type/ZhongDaoDaXue.png");
    mTypeMap.insert("中到大雨",":/res/type/ZhongDaoDaYu.png");
    mTypeMap.insert("中雪",":/res/type/ZhongXue.png");
    mTypeMap.insert("中雨",":/res/type/ZhongYu.png");
}


Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        menuQuit->exec(QCursor::pos());
    }
    //鼠标当前位置 event->globalPos();，
    //窗口当前位置 this->pos()窗口新位置event->globalPos() - mOffset
    if(event->button() == Qt::LeftButton){
        mOffset = event->globalPos()-this->pos();
    }
}
//鼠标左键按下后的移动，导致这个事件被调用，设置窗口的新位置
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - mOffset);
}

void Widget::parseWeatherJsonData(QByteArray rawData)
{
    QJsonDocument jsonObj = QJsonDocument::fromJson(rawData);
    if(!jsonObj.isNull() && jsonObj.isObject()){
        QJsonObject objRoot = jsonObj.object();
        //解析日期
        QString date = objRoot["date"].toString();
        QString week = objRoot["week"].toString();
        ui->labelCurrentDate->setText(date+"  "+week);
        //解析城市名称
        QString cityName = objRoot["city"].toString();
        ui->labelCity->setText(cityName+"市");
        //解析当前温度
        QString currentTemp = objRoot["tem"].toString();
        ui->labelTmp->setText(currentTemp+"℃");
        ui->labelTempRange->setText(objRoot["tem2"].toString()+"~"
                +objRoot["tem1"].toString());
        //解析天气类型
        ui->labelweatherType->setText(objRoot["wea"].toString());
        ui->labelWeatherIcon->setPixmap(mTypeMap[objRoot["wea"].toString()]);
        //感冒指数
        ui->labelGaomao->setText(objRoot["air_tips"].toString());
        //风向
        ui->labelFXType->setText(objRoot["win"].toString());
        //风力
        ui->labelFXType_2->setText(objRoot["win_speed"].toString());
        //PM2.5
        ui->labelPM25Data->setText(objRoot["air_pm25"].toString());
        //湿度
        ui->labelShiduData->setText(objRoot["humidity"].toString());
        //空气质量
        ui->labelairData->setText(objRoot["air_level"].toString());

    }
}

void Widget::parseWeatherJsonDataNew(QByteArray rawData)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData);
    if( !jsonDoc.isNull() && jsonDoc.isObject()){
        QJsonObject jsonRoot = jsonDoc.object();
        days[0].mCity = jsonRoot["city"].toString();
        days[0].mPm25 = jsonRoot["aqi"].toObject()["pm25"].toString();
        if( jsonRoot.contains("data") && jsonRoot["data"].isArray()){
            QJsonArray weaArray = jsonRoot["data"].toArray();
            for(int i = 0; i < weaArray.size(); i++){
                QJsonObject obj = weaArray[i].toObject();
                //qDebug() << obj["date"].toString() << obj["wea"].toString();
                days[i].mDate = obj["date"].toString();
                days[i].mWeek = obj["week"].toString();
                days[i].mWeathType = obj["wea"].toString();
                days[i].mTemp = obj["tem"].toString();
                days[i].mTempLow = obj["tem2"].toString();
                days[i].mTempHigh = obj["tem1"].toString();
                days[i].mFx = obj["win"].toArray()[0].toString();
                days[i].mFl = obj["win_speed"].toString();
                days[i].mAirq = obj["air_level"].toString();
                days[i].mTips = obj["air_tips"].toString();
                days[i].mHu = obj["humidity"].toString();


            }
        }
    }
    updateUI();
}

void Widget::updateUI()
{
    QPixmap pixmap;

    //解析日期
    ui->labelCurrentDate->setText(days[0].mDate+"  "+days[0].mWeek);
    //解析城市名称
    ui->labelCity->setText(days[0].mCity+"市");
    //解析当前温度
    ui->labelTmp->setText(days[0].mTemp+"℃");
    ui->labelTempRange->setText(days[0].mTempLow+"～"
            +days[0].mTempHigh);
    //解析天气类型
    ui->labelweatherType->setText(days[0].mWeathType);
    ui->labelWeatherIcon->setPixmap(mTypeMap[days[0].mWeathType]);
    //感冒指数
    ui->labelGaomao->setText(days[0].mTips);
    //风向
    ui->labelFXType->setText(days[0].mFx);
    //风力
    ui->labelFXType_2->setText(days[0].mFl);
    //PM2.5
    ui->labelPM25Data->setText(days[0].mPm25);
    //湿度
    ui->labelShiduData->setText(days[0].mHu);
    //空气质量
    ui->labelairData->setText(days[0].mAirq);

    ui->lbweatherTypeDate3->setText(days[3].mWeathType);
    ui->lbweatherTypeDate0->setText(days[0].mWeathType);

    for(int i = 0; i < 6; i++){


        mWeekList[i]->setText(days[i].mWeek);
        mWeekList[0]->setText("今天");
        mWeekList[1]->setText("明天");
        mWeekList[2]->setText("后天");
        QStringList dayList = days[i].mDate.split("-");
        mDateList[i]->setText(dayList.at(1)+"-"+dayList.at(2));//2024-01-24

        //缩放图片大小和label大小能匹配
        int index = days[i].mWeathType.indexOf("转");
        if(index != -1){
            pixmap = mTypeMap[days[i].mWeathType.left(index)];
        }else{
            pixmap = mTypeMap[days[i].mWeathType];
        }
        pixmap = pixmap.scaled(mIconList[i]->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        mIconList[i]->setMaximumHeight(50);
        mIconList[i]->setMaximumWidth(ui->widget02->width()/6.5);
        mIconList[i]->setPixmap(pixmap);
        mWeaTypeList[i]->setText(days[i].mWeathType);

        QString airQ = days[i].mAirq;
        mAirqList[i]->setText(airQ);
        if( airQ == "优"){
             mAirqList[i]->setStyleSheet("background-color: rgb(150, 213, 32); border-radius: 7px; color: rgb(230, 230, 230)");
        }
        if( airQ == "良"){
             mAirqList[i]->setStyleSheet("background-color: rgb(208, 107, 39); border-radius: 7px; color: rgb(230, 230, 230)");
        }
        if( airQ == "轻度"){
             mAirqList[i]->setStyleSheet("background-color: rgb(255, 199, 199); border-radius: 7px; color: rgb(230, 230, 230)");
        }
        if( airQ == "中度"){
             mAirqList[i]->setStyleSheet("background-color: rgb(255, 17, 17); border-radius: 7px; color: rgb(230, 230, 230)");
        }
        if( airQ == "重度"){
             mAirqList[i]->setStyleSheet("background-color: rgb(153, 0, 0); border-radius: 7px; color: rgb(230, 230, 230)");
        }



        mFxList[i]->setText(days[i].mFx);
        index = days[i].mFl.indexOf("转");
        if(index != -1){
            mFlList[i]->setText(days[i].mFl.left(index));
        }else{
            mFlList[i]->setText(days[i].mFl);
        }



    }
}



void Widget::readHttpRply(QNetworkReply *reply)
{
    int resCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    // qDebug() << resCode;
    if( reply->error() == QNetworkReply::NoError && resCode == 200){
        //大多数服务器返回的字符编码格式是utf-8
        QByteArray data = reply->readAll();
        //parseWeatherJsonData(data);
        parseWeatherJsonDataNew(data);
        // qDebug() << QString::fromUtf8(data);
    }else{
        // QMessageBox::warning(this,"错误","网络请求失败",QMessageBox::Ok);
        QMessageBox mes;
        mes.setWindowTitle("错误");
        mes.setText("网络请求失败");
        mes.setStyleSheet("QPushButton {color:red}");
        mes.setStandardButtons(QMessageBox::Ok);
        mes.exec();
    }
}

void Widget::on_pushButton_clicked()
{
    QString cityNameFromUser = ui->lineEditCity->text();
    QString cityCode = cityCodeUtils.getCityCodeFromName(cityNameFromUser);
    if(cityCode != NULL){
        strUrl += "&cityid=" + cityCode;
        qDebug() << strUrl;
        manager->get(QNetworkRequest(QUrl(strUrl)));
    }else{
        QMessageBox mes;
        mes.setWindowTitle("错误");
        mes.setText("请输入正确的城市名");
        mes.setStyleSheet("QPushButton {color:red}");
        mes.setStandardButtons(QMessageBox::Ok);
        mes.exec();
    }
}
