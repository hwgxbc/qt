#include "mytextedit.h"

#include <QWheelEvent>
#include <QDebug>

MyTextEdit::MyTextEdit(QWidget *parent) : QTextEdit(parent)
{

}

void MyTextEdit::wheelEvent(QWheelEvent *e)
{
    //qDebug() << e->angleDelta().y();
    if(ctrlKeyPressed == 1){
        if(e->angleDelta().y() > 0){
            zoomIn(15);
        }else if(e->angleDelta().y() < 0){
            zoomOut(15);
        }
        e->accept();
    }else{
        QTextEdit::wheelEvent(e);
    }
}

void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control){
       // qDebug() << "ctrl Pressed";
        ctrlKeyPressed = 1;
    }
    QTextEdit::keyPressEvent(e);
}

void MyTextEdit::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control){
       // qDebug() << "ctrl Release";
        ctrlKeyPressed = 0;
    }
    QTextEdit::keyPressEvent(e);
}
