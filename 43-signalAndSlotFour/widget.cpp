#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //�ڹ��캯���н����ź���۵İ�
    //�ڶ��ַ�ʽ��QObject::connect(sender, SIGNAL(signal()), receiver, SLOT(slot()));
    QObject::connect(ui->btnCon, SIGNAL(clicked()), this, SLOT(on_btnCon_clickedMyself()));

    //������ʽ��lambda���ʽ��QObject::connect(sender, &Sender::signal, [=]() { /* lambda body */ });
    QObject::connect(ui->btnLambda, &QPushButton::clicked,[=](){
        std::cout << "btnLambdaClicked" << std::endl;
    });
    //�����ַ�ʽ��QObject::connect(sender, &Sender::signal, receiver, &Receiver::slot);
    QObject::connect(ui->btnFortch,&QPushButton::clicked,this,&Widget::on_fortch_clicked);
}

Widget::~Widget()
{
    delete ui;
}

//��һ�ַ�ʽ��ͨ��uiDesigner
void Widget::on_btnui_clicked()
{
    std::cout << "UIBtnClicked" << std::endl;
}

void Widget::on_btnCon_clickedMyself()
{
    std::cout << "btnConClicked" << std::endl;
}

void Widget::on_fortch_clicked()
{
    std::cout << "btnForthClicked" << std::endl;
}
