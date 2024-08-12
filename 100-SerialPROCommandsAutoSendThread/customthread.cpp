#include "customthread.h"



void CustomThread::run()
{
    while(true){
        msleep(1000);
        emit threadTimeout();
    }
}

CustomThread::CustomThread(QWidget *parent) : QThread(parent)
{

}
