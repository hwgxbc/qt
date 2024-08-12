#ifndef WIDGET_H
#define WIDGET_H

#include <QMenu>
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
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    QMenu *menuQuit;
};
#endif // WIDGET_H
