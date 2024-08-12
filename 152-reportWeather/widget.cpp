#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFont(QFont("Arial",15));
    setFixedSize(507,936);
    setWindowFlag(Qt::FramelessWindowHint);
}

Widget::~Widget()
{
    delete ui;
}

