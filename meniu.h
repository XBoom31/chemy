#ifndef MENIU_H
#define MENIU_H

#include <QMainWindow>
#include <QPainter>
#include "utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Meniu; }
QT_END_NAMESPACE

class Meniu : public QMainWindow
{
    Q_OBJECT

public:
    Meniu(QWidget *parent = nullptr);
    ~Meniu();

public slots:
    void selected_element_changed();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_2_pressed();

    void on_viz3d_pressed();

    void on_lectii_clicked();

private:
    Ui::Meniu *ui;
};
#endif // MENIU_H
