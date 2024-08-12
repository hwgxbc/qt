#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QWheelEvent>

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
void Widget::enterEvent(QEvent *event)
{
    qDebug() << "mouse enter";
}
void Widget::leaveEvent(QEvent *event)
{
    qDebug() << "mouse leave";
}
void Widget::wheelEvent(QWheelEvent *event)
{
    qDebug() << event->angleDelta();

}
void Widget::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::warning(this, tr("My Application"),
                                    tr("close the window\n"
                                       "Do you want to close the window?"),
                                    QMessageBox::Ok | QMessageBox::No
                                    );
    switch(ret){
    case QMessageBox::Ok:
        event->accept();
        break;
    case QMessageBox::No:
        event->ignore();
        break;
    }

}
void Widget::resizeEvent(QResizeEvent *event)
{
    qDebug() << "oldSize:" << event->oldSize()
             << "newSize:" << event->size();
}

void Widget::on_pushButton_clicked()
{

}
