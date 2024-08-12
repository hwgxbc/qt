#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::Widget *ui;
    QTimer *timer;
    int currentValue;
    int mark = 0;
    int startAngle;
    double angle;
    void initCanvas(QPainter& painter);
    void drawMiddleCircle(QPainter& painter,int radius);
    void drawCurrentSpeed(QPainter& painter);
    void drawScale(QPainter& painter,int radius);
    void drawScaleText(QPainter& painter,int radius);
    void drawPointLine(QPainter &painter,int lenth);
    void drawSpeedPie(QPainter& painter,int radius);
    void startSpeed();
};
#endif // WIDGET_H
