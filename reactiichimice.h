#ifndef REACTIICHIMICE_H
#define REACTIICHIMICE_H

#include <QMainWindow>
#include <QPainter>


struct solutie{
    char* mdname; // Ex: NaCl
    float md;     // Ex: 20 g NaCl
    float mdmass; // 20(na) + 32 Cl = 52g masa atomica
    float mh;     // masa apa
};

namespace Ui {
class reactiichimice;
}

class reactiichimice : public QMainWindow
{
    Q_OBJECT

public:
    explicit reactiichimice(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);
    ~reactiichimice();

private slots:
    void on_balancebtn_clicked();

    void on_balt_clicked();

    void on_bverifica_clicked();

private:
    std::vector<std::string> reactii;
    int x,y,w,h,nr; //pentru vizualizare 2d solutie
    int c1,c2,c3; // pentru balansator
    QImage atomz[10];
    QString balance(QString str);
    QString process(QString str);
    void createatom(QPainter& painter, int type);
    Ui::reactiichimice *ui;
};

#endif // REACTIICHIMICE_H
