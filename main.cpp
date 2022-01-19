#include "meniu.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <fstream>
#include "vars.h"
#include <iostream>
#include <QFile>

vvars vars;

using namespace std;

vector<string> sdata;
int id = 0,maxid = 0;

#define nr(x) atof(x.toStdString().c_str());

void loadtabel(){
       QFile freac(":/home/impl38/dev/chimie/gov_elem");
       freac.open(QFile::ReadOnly);
       QTextStream str(&freac);
       QString line;
       vector<string> sdata;
       int maxid = 0;
       while (str.readLineInto(&line)) {
          sdata.push_back(line.toStdString());
          maxid++;
       }
       if(!maxid)
           return;
       for(int i = 0; i<maxid; i++){
           QString temp = sdata[i].c_str();
           temp.remove("\"");
           auto pieces = temp.split(",");
           if(pieces.length() != 18){
               cout << pieces.length();
               //gov_elem nu e facut bine, nici macar atat nu iti dau de gratis americanii..
               //daca dam continue nu punem numai elementele bune, numai ca ramanem fara jumate
               //continue;
           }
           cout << pieces[1].toStdString().c_str();
           //trebuie sa combini indexul 10 cu 11, n-ai csf
           const string sym = pieces[1].toStdString();
           const string nume = pieces[2].toStdString();
          // const string color = pieces[4].toStdString();
           vars.tabel[i].natomic = nr(pieces[0]);
           vars.tabel[i].sym = sym;
           vars.tabel[i].nume = nume;
           vars.tabel[i].atomic_mass = nr(pieces[3]);
           vars.tabel[i].color = (const string)pieces[4].toStdString(); // potential crash
           vars.tabel[i].electron_conf = (const string)pieces[5].toStdString();
           vars.tabel[i].electron_negativity = nr(pieces[6]);
           vars.tabel[i].rad_atom = nr(pieces[7]);
           vars.tabel[i].ionization_energy = nr(pieces[8]);
           vars.tabel[i].electron_affinity = nr(pieces[9]);
           vars.tabel[i].oxidation_states = (const string)(pieces[10] + " " + pieces[11]).toStdString();
           vars.tabel[i].standard_state = (const string)pieces[12].toStdString();
           vars.tabel[i].melting_point = nr(pieces[13]);
           vars.tabel[i].boiling_point = nr(pieces[14]);
           vars.tabel[i].density = nr(pieces[15]);
           vars.tabel[i].group_block = (const string)pieces[16].toStdString();
           //vars.tabel[i].year = nr(pieces[17]);
       }
}

//numai daca porneste direct in reactii chimie
//#include "reactiichimice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QResource::registerResource("resources.qrc");
    loadtabel();
    Meniu w;
    w.show();

    //reactiichimice rc;
    //rc.show();

    return a.exec();
}
