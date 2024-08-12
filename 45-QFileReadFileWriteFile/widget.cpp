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


void Widget::on_pushButton_clicked()
{
    QFile file("D:/QT/test.txt");
    if (!file.open(QIODevice::ReadOnly))
        return;
    char datas[100];
    file.exists();
    file.read(datas,100);
    qDebug() << datas;

    file.close();
    file.setFileName("D:/QT/test2.txt");
    file.open(QIODevice::WriteOnly);
    file.write("this is a new file Created");
}
