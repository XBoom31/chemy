#include "viselem.h"
#include "ui_viselem.h"
#include "vis3d.h"
#include "vars.h"

//sa fie frumos
#define QS(x) QString(vars.tabel[vars.selected_element].x.c_str())
#define QN(a) QString::number(x.a)
#define Set(x,a) ui->x->setText(a)

viselem::viselem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viselem)
{
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint); //Makes the frame invisible
    this->setWindowState(Qt::WindowMaximized); //Maximizes the window

    vis3d* v3d = new vis3d();
    v3d->create_window();
    auto container = QWidget::createWindowContainer(v3d->get_view());
    ui->horizontalLayout->addWidget(container);
    ui->verticalLayout->setAlignment(ui->label, Qt::AlignHCenter);


    element x = vars.selected_element ? vars.tabel[vars.selected_element-1] : vars.tabel[vars.selected_element];

    Set(lnatomic,             "Numar Atomic: "                + QN(natomic));
    Set(lnume,                "Nume: "                        + QS(nume));
    Set(lsym,                 "Simbol: "                      + QS(sym));
    Set(latomic_mass,         "Masa atomica: "                + QN(atomic_mass));
    Set(lcolor,               "Culoare HEX: "                 + QS(color));
    Set(lelectron_conf,       "Configuratia electronilor: "   + QS(electron_conf));
    Set(lelectron_negativity, "Negativitate electronilor: "   + QN(electron_negativity));
    Set(lrad_atom,            "Raza Atomului: "               + QN(rad_atom));
    Set(lionization_energy,   "Energie de ionizare: "         + QN(ionization_energy));
    Set(lelectron_affinity,   "Afinitatea electronilor: "     + QN(electron_affinity));
    Set(loxidation_states,    "OxidationStates: "             + QS(oxidation_states));
    Set(lstandard_state,      "Stare: "                       + QS(standard_state));
    Set(lmelting_point,       "Punct de topire: "             + QN(melting_point));
    Set(lboiling_point,       "Punct de fierbere: "           + QN(boiling_point));
    Set(ldensity,             "Densitate: "                   + QN(density));
    Set(lgroup_block,         "Categorie: "                   + QS(group_block));
    Set(lyear,                "Anul descoperirii: "           + QN(year));


}

viselem::~viselem()
{
    delete ui;
}

void viselem::on_pushButton_clicked()
{
    this->hide();
}

