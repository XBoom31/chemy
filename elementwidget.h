#ifndef ELEMENTWIDGET_H
#define ELEMENTWIDGET_H

#include <QWidget>
#include "vars.h"
#include <QPainter>

namespace Ui {
class Elementwidget;
}

class Elementwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Elementwidget(QWidget *parent = nullptr);
    ~Elementwidget();
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void elementChanged();

private:
    Ui::Elementwidget *ui;
    element e;
    int ox, oy;
};

#endif // ELEMENTWIDGET_H
