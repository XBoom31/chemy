#include "elementwidget.h"
#include "ui_elementwidget.h"
#include <QFontMetrics>
#include <iostream>
#include <QPainterPath>
Elementwidget::Elementwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Elementwidget)
{
    ui->setupUi(this);
    e = vars.tabel[vars.current_element];

}

Elementwidget::~Elementwidget()
{
    delete ui;
}


QFont font_sym("Times", 20, QFont::Bold);
QFontMetrics symm(font_sym);
QFont font_na("Times", 15, QFont::Normal);
QFontMetrics nam(font_na);
QFont font_name("Times",10, QFont::Normal);
QFontMetrics namem(font_name);
void Elementwidget::paintEvent(QPaintEvent *event)
{
    int w_sym = symm.horizontalAdvance(e.sym.c_str());
    int w_na = nam.horizontalAdvance(QString::number(e.natomic));
    int w_nu = namem.horizontalAdvance(e.nume.c_str());
    QPainter painter(this);

    QPainterPath bg;
    bg.addRect(0,0,60,80);
    //painter.fillPath(bg, vars.ecol);
    painter.drawRect(0, 0,60,80);

    for(auto r : elem_cu_rosu)
        if(e.sym == r)
            painter.setPen(Qt::red);
    for(auto r : elem_cu_verde)
        if(e.sym == r)
            painter.setPen(Qt::green);
    painter.setFont(font_sym);
    painter.drawText(30 - w_sym / 2, 50, e.sym.c_str());
    painter.setPen(Qt::white);
    painter.setFont(font_na);
    painter.drawText(30 - w_na / 2, 15, QString::number(e.natomic));
    painter.setFont(font_name);
    painter.drawText(30 - w_nu / 2, 65, e.nume.c_str());
}

#include "viselem.h"

void Elementwidget::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << "clicked\n";
    vars.selected_element = e.natomic - 1;
    emit elementChanged();

    auto vis = new viselem();
    vis->show();

}

