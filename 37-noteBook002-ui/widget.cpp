#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //��Ȼ����һ�д������widget��ui�Ĵ��ڹ�������������������ڴ�С�仯��ʱ������Ĳ��ֲ�����֮�仯
    //ͨ���������д��������ʾ˵�����ô��ڱ仯ʱ�����ּ����ӿؼ���֮����
    this->setLayout(ui->verticalLayout);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnFileOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "D:/QT/",
                                                    tr("Text (*.txt)"));

    ui->textEdit->clear();

    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "file open error";
    }

    QTextStream in(&file);
   // in.setCodec("UTF-8");
    in.setCodec("ANSI");
    while(!in.atEnd()){
        QString context = in.readLine();
       // qDebug() << qPrintable(context);
       // ui->textEdit->setText(context);
        ui->textEdit->append(context);
    }
}

void Widget::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "D:/QT/untitled.txt",
                                tr("Text (*.txt *.doc)"));

    file.setFileName(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "file open error";
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    QString context = ui->textEdit->toPlainText();
    out << context;
}

void Widget::on_btnClose_clicked()
{

    if(file.isOpen()){

        file.close();
        ui->textEdit->clear();
    }
}
