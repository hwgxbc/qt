#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnRead_clicked()
{
    //1. 打开文件
    //QFile file("D:/QT/test.txt");
    QFile file;
    file.setFileName("D:/QT/test.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "file open error";
    }
    int size = file.size();
    //2. 读取文件
   // char context[size] = {'\0'};
    char* context = new char(size);
    if( file.read(context,100) == -1)  return;
    //3. 输出文件内容
    qDebug() << context;
    file.close();
}

void Widget::on_btnWrite_clicked()
{
   // 1.打开
    QFile file("D:/QT/test2.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
   // 2. 写入
    file.write("Program 45-QFile001 write something to This File 我是老陈");
   // 3. 关闭
    file.close();
}

void Widget::on_btnstrRead_clicked()
{
    QFile file;
    file.setFileName("D:/QT/test.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "file open error";
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
   // QString context = in.read(file.size());
    while(!in.atEnd()){
        QString context = in.readLine();
        qDebug() << context;
        qDebug() << "--------";
    }

    file.close();
}

void Widget::on_btnstreamWrite_clicked()
{
    QFile file;
    file.setFileName("D:/QT/test3.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "file open error";
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << "I write stream char to File";
    file.close();
}
