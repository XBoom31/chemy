#include "meniu.h"
#include "ui_meniu.h"
#include "elementwidget.h"
#include "reactiichimice.h"

#define c(a) vars.ecol = QColor(QRgb(a))

Meniu::Meniu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Meniu)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowState(Qt::WindowMaximized); //Maximizes the window
    //ui->verticalLayout->setAlignment(ui->label, Qt::AlignHCenter);
    int c = 0;
    for(int y=0; y<9; y++){
        for(int x = 0; x<18; x++){

        }
    }

    //prima linie

    vars.current_element = 0;
    auto h = new Elementwidget(this);
    ui->gridLayout->addWidget(h, 0, 0);
    vars.current_element++;

    auto he = new Elementwidget(this);
    ui->gridLayout->addWidget(he, 0, 17);
    vars.current_element++;

    //a doua linie

    auto li = new Elementwidget(this);
    ui->gridLayout->addWidget(li, 1, 0);
    vars.current_element++;

    auto be = new Elementwidget(this);
    ui->gridLayout->addWidget(be, 1, 1);
    vars.current_element++;
    c(0x2aa737);
    for(int i = 13; i <= 18; i++){
        auto e = new Elementwidget(this);
        ui->gridLayout->addWidget(e,1,i-1);
        vars.current_element++;
    }

    //a treia linie
    auto na = new Elementwidget(this);
    ui->gridLayout->addWidget(na, 2, 0);
    vars.current_element++;
    auto mg = new Elementwidget(this);
    ui->gridLayout->addWidget(mg, 2, 1);
    vars.current_element++;
    for(int i = 13; i <= 18; i++){
        auto e = new Elementwidget(this);
        ui->gridLayout->addWidget(e,2,i-1);
        vars.current_element++;
    }

    //a patra linie
    for(int i = 0; i <= 17; i++){
        auto e = new Elementwidget(this);
        ui->gridLayout->addWidget(e,3,i);
        vars.current_element++;
    }

    //a cincia linie
    for(int i = 0; i <= 17; i++){
        auto e = new Elementwidget(this);
        ui->gridLayout->addWidget(e,4,i);
        vars.current_element++;
    }

    //a sasea linie
    auto cs = new Elementwidget(this);
    ui->gridLayout->addWidget(cs,5,0);
    vars.current_element++;
    auto ba = new Elementwidget(this);
    ui->gridLayout->addWidget(ba,5,1);
    vars.current_element++;
    for(int i = 3; i <= 17; i++){
        auto e = new Elementwidget(this);
        ui->gridLayout->addWidget(e,7,i-1);
        vars.current_element++;
    }
    for(int i = 4; i <= 18; i++){
        auto e = new Elementwidget(this);
        ui->gridLayout->addWidget(e,5,i-1);
        vars.current_element++;
    }

    //a saptea linie
    auto fr = new Elementwidget(this);
    ui->gridLayout->addWidget(fr,6,0);
    vars.current_element++;
    auto ra = new Elementwidget(this);
    ui->gridLayout->addWidget(ra,6,1);
    vars.current_element++;
    for(int i = 3; i <= 17; i++){
        auto e = new Elementwidget(this);
        ui->gridLayout->addWidget(e,8,i-1);
        vars.current_element++;
    }
    for(int i = 4; i <= 18; i++){
        auto e = new Elementwidget(this);
        ui->gridLayout->addWidget(e,6,i-1);
        vars.current_element++;
    }

    //ui->gridLayout->

}

Meniu::~Meniu()
{
    delete ui;
}




void Meniu::selected_element_changed(){

}

void Meniu::on_pushButton_2_pressed()
{
    auto WReactiiChimice = new reactiichimice();
    WReactiiChimice->show();
}


void Meniu::on_pushButton_2_clicked()
{

}


void Meniu::on_viz3d_pressed()
{
    //if(vars.vizualizator3d)
   //    delete vars.vizualizator3d;
    //vars.vizualizator3d = new vis3d();
    auto a = new vis3d();
    a->create_window();
    hide();

    //vars.vizualizator3d.create_window();
}


void Meniu::on_lectii_clicked()
{
    system("firefox badeaadrian.go.ro/chimie/lectii");
}

