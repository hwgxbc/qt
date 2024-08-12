#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        qDebug() << "timer out!";
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    timer->start(1000);
}

void Widget::on_pushButton_2_clicked()
{
    timer->stop();
}

void Widget::on_checkBox_clicked()
{
    if(ui->checkBox->checkState() ==  Qt::Checked){
        qDebug() << "checkBox checked!";
    }
    if(ui->checkBox->checkState() ==  Qt::Unchecked){
        qDebug() << "checkBox unchecked!";
    }
}

void Widget::on_checkBox_clicked(bool checked)
{
    qDebug() << "checkBox status!" << checked;
}
