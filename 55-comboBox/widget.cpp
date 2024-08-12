#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(oncurrentIndexChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::oncurrentIndexChanged(int index)
{
    qDebug() << index;
    qDebug() << ui->comboBox->currentText();
}

