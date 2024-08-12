#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //虽然上面一行代码进行widget和ui的窗口关联，但是如果发生窗口大小变化的时候，里面的布局不会随之变化
    //通过下面这行代码进行显示说明，让窗口变化时，布局及其子控件随之调整
    this->setLayout(ui->verticalLayout);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onCurrentIndexChanged(int)));
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(onCursorPositionChanged()));
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
    this->setWindowTitle(fileName + "- MyNoteBook");
    QTextStream in(&file);
   // in.setCodec("UTF-8");
   // in.setCodec("ANSI");
    //in.setCodec(ui->comboBox->currentText().toStdString().c_str());
    QString str = ui->comboBox->currentText();//把QString转化成char *
    const char* c_str = str.toStdString().c_str();

    in.setCodec(c_str);
    while(!in.atEnd()){
        QString context = in.readLine();
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
    this->setWindowTitle(fileName + "- MyNoteBook");
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
        this->setWindowTitle("MyNoteBook");
    }
}

void Widget::onCurrentIndexChanged(int index)
{
    qDebug() << "currentItSignal";
    ui->textEdit->clear();
    if(file.isOpen()){
        qDebug() << "file is Open";
        QTextStream in(&file);
        in.setCodec(ui->comboBox->currentText().toStdString().c_str());
        file.seek(0);
        while(!in.atEnd()){
            QString context = in.readLine();
            ui->textEdit->append(context);
        }
    }
}

void Widget::onCursorPositionChanged()
{

    QTextCursor cursor =  ui->textEdit->textCursor();
    //qDebug() << cursor.blockNumber()+1  <<","<< cursor.columnNumber() + 1;

    QString blockNum = QString::number(cursor.blockNumber()+1);
    QString columnNum = QString::number(cursor.columnNumber()+1);

    const QString labelMes = "L:"+blockNum+",C:"+columnNum+"   ";
    //const QString labelMes = "行:"+blockNum+",列:"+columnNum+"   ";
    ui->labelPosition->setText(labelMes);
}
