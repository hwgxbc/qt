#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) //��ʼ���б�������
{
    ui->setupUi(this);//����QTdesigner�����ui������widget���˽�б���ui����



}

Widget::~Widget()
{
    delete ui;
}

