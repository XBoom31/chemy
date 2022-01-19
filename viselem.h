#ifndef VISELEM_H
#define VISELEM_H

#include <QWidget>

namespace Ui {
class viselem;
}

class viselem : public QWidget
{
    Q_OBJECT

public:
    explicit viselem(QWidget *parent = nullptr);
    ~viselem();

private slots:
    void on_pushButton_clicked();

private:
    Ui::viselem *ui;
};

#endif // VISELEM_H
