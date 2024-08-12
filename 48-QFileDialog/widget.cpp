#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QDebug>
#include <QTextCodec>

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


void Widget::on_btnQFileDialog_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "D:/QT/",
                                                    tr("Text (*.txt)"));
    qDebug() << fileName;

    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "file open error";
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
   // QString context = in.read(file.size());
    while(!in.atEnd()){
        QString context = in.readLine();
        qDebug() << qPrintable(context);

    }

    file.close();

}

void Widget::on_btnSe_clicked()
{

    QFileDialog qFileDialog;
    qFileDialog.setFileMode(QFileDialog::ExistingFiles);
    qFileDialog.setNameFilter("*.txt");
    qFileDialog.exec();
    QStringList qstrings =  qFileDialog.selectedFiles();
    for(QString str : qstrings){
        qDebug() << str;
    }
}


void Widget::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "D:/QT/untitled.txt",
                                tr("Text (*.txt *.doc)"));
    qDebug()<<fileName;
    QFile file;
    file.setFileName(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "file open error";
    }

    QTextStream out(&file);
    out.setCodec(QTextCodec::codecForName("UTF-16BE"));
    out << "Qdialog Write Data to the Txt FileÄãºÃ";
    file.close();
}
