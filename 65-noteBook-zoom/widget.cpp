#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>
#include <QWheelEvent>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QShortcut *shortcutOpen = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")),this);
    QShortcut *shortcutSave = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")),this);
    QShortcut *shortcutZoomIn = new QShortcut(QKeySequence(tr("Ctrl+Shift+=", "File|Save")),this);
    QShortcut *shortcutZoomOut = new QShortcut(QKeySequence(tr("Ctrl+Shift+-", "File|Save")),this);

    connect(shortcutOpen,&QShortcut::activated,[=](){
        on_btnFileOpen_clicked();
    });

    connect(shortcutSave,&QShortcut::activated,[=](){
        on_btnSave_clicked();
    });

    connect(shortcutZoomIn,&QShortcut::activated,[=](){
        zoomIn();
    });
    connect(shortcutZoomOut,&QShortcut::activated,[=](){
        zoomOut();
    });

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

void Widget::zoomIn()
{
    //获得TextEdit的当前字体信息
    QFont font = ui->textEdit->font();
    //获得当前字体的大小
    int fontSize = font.pointSize();
    if(fontSize == -1) return;

    //改变大小，并设置字体大小
    int newFontSize = fontSize+1;
    font.setPointSize(newFontSize);
    ui->textEdit->setFont(font);
}

void Widget::zoomOut()
{
    //获得TextEdit的当前字体信息
    QFont font = ui->textEdit->font();
    //获得当前字体的大小
    int fontSize = font.pointSize();
    if(fontSize == -1) return;

    //改变大小，并设置字体大小
    int newFontSize = fontSize-1;
    font.setPointSize(newFontSize);
    ui->textEdit->setFont(font);
}


void Widget::on_btnFileOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "D:/QT/",
                                                    tr("Text (*.txt)"));

    ui->textEdit->clear();

    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
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
    if(!file.isOpen()){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "D:/QT/untitled.txt",
                                                        tr("Text (*.txt *.doc)"));

        file.setFileName(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            qDebug() << "file open error";
        }
        this->setWindowTitle(fileName + "- MyNoteBook");

    }
    QTextStream out(&file);
    out.setCodec(ui->comboBox->currentText().toStdString().c_str());
    QString context = ui->textEdit->toPlainText();
    out << context;
}

void Widget::on_btnClose_clicked()
{

    QMessageBox msgBox;

    int ret = QMessageBox::warning(this, tr("MyNoteBook Notice:"),
                                   tr("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard
                                   | QMessageBox::Cancel,
                                   QMessageBox::Save);

    switch (ret) {
    case QMessageBox::Save:
        // Save was clicked
        on_btnSave_clicked();
        qDebug() << "QMessageBox::Save:";
        break;
    case QMessageBox::Discard:
        // Don't Save was clicked
        ui->textEdit->clear();
        if(file.isOpen()){
            file.close();
            this->setWindowTitle("MyNoteBook");
        }
        qDebug() << "QMessageBox::Discard:";
        break;
    case QMessageBox::Cancel:
        // Cancel was clicked
        qDebug() << "QMessageBox::Cancel:";
        break;
    default:
        // should never be reached
        break;
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


    //设置当前行高亮
    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection ext;

    //1. 知道当前行
    ext.cursor = cursor;

    QBrush qBrush(Qt::lightGray);
    //2. 颜色
    ext.format.setBackground(qBrush);
    //配置段属性：整行显示，没有这句话不行
    ext.format.setProperty(QTextFormat::FullWidthSelection, true);
    //ext.format.setFontUnderline(true);
    //3. 设置
    //把ext加到ext的容器中
    extraSelections.append(ext);
    ui->textEdit->setExtraSelections(extraSelections);
}
